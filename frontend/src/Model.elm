port module Model exposing (Model, init, store, toJson, fromJson, buildQuery)

import Message     as Msg exposing (Message)
import Query       as Qry exposing (Query)
import Path        as Pth exposing (Path)
import Dict        as Dct exposing (Dict)
import Json.Encode as JsE
import Json.Decode as JsD
import Navigation  as Nav
import WebSocket   as WSk
import Config      as Cfg
import Maybe       as Myb


{- TYPES AND CONSTANTS -}

type alias Secret = 
    {
        password  : String,
        password2 : String
    }

type ReleaseMode = Public | Private

type alias Model =
    {
        path         : Path,
        username     : String,
        email        : String,
        server_reply : String,
        secret       : Secret
    }

default = 
    {
        path         = Pth.LogIn,
        username     = "",
        email        = "",
        server_reply = "",
        secret       =
            {
                password  = "",
                password2 = ""
            } 
    }

{- LOCAL STORAGE -}

port setStorage : JsD.Value -> Cmd msg

store : (Model, Cmd Message) -> (Model, Cmd Message)
store (model, cmd) = 
    (model, Cmd.batch [setStorage (toJson Public model), cmd])

{- INIT -}

changePath : Path -> Model -> (Model, Cmd Message)
changePath path model =
    {model | path = path} ! []

init : Maybe JsD.Value -> Nav.Location -> (Model, Cmd Message)
init flag location = 
    case flag of 
        Just json ->
            changePath (Pth.fromLocation location) (fromJson json)
        Nothing ->
            changePath (Pth.fromLocation location) default

{- JSON ENCODING / DECODING -}

secretToJson : Secret -> JsE.Value
secretToJson secret =
    JsE.object
        [
            ("password" , JsE.string secret.password ),
            ("password2", JsE.string secret.password2)
        ]


secretFromJson : JsD.Decoder Secret
secretFromJson =
    JsD.map2 Secret
        (JsD.field "password" JsD.string)
        (JsD.field "password" JsD.string)

toJson : ReleaseMode -> Model -> JsE.Value
toJson releaseMode model =
    let
        secret = 
            case releaseMode of
                Private -> secretToJson model.secret
                Public -> JsE.object []

    in
        JsE.object
            [   
                ("path"          , JsE.string (Pth.toString model.path)),
                ("username"      , JsE.string model.username           ),
                ("email"         , JsE.string model.email              ),
                ("server_reply", JsE.string model.server_reply         ),
                ("secret"        , secret                              )
            ]

fromJson : JsD.Value -> Model
fromJson json =
    let
        decoderRoot   = JsD.dict (JsD.maybe JsD.string)
        decoderSecret = JsD.at ["secret"] secretFromJson
        decodedRoot   = JsD.decodeValue decoderRoot   json
        decodedSecret = JsD.decodeValue decoderSecret json
    in
        case decodedRoot of
            Ok root ->
                let
                    getRoot = \s -> root |> Dct.get s
                                         |> Myb.withDefault Myb.Nothing
                                         |> Myb.withDefault ""
                in
                    case decodedSecret of
                        Ok secret ->
                            Model
                                (Pth.fromString (getRoot "path"))
                                (getRoot "username")
                                (getRoot "email")
                                (getRoot "server_reply")
                                secret
                        _ -> default
            _ -> default

buildQuery : Model -> Query -> String
buildQuery model query =
    JsE.object 
        [
            ("server_query", query |> Qry.toString 
                                   |> JsE.string),
            ("model", toJson Private model)
        ]
    |> JsE.encode Cfg.jsonIndent