port module Model exposing (..)

import Message     as Msg exposing (Message)
import Json.Decode as JsD exposing ((:=))
import Path        as Pth exposing (Path)
import Json.Encode as JsE
import Config      as Cfg
import Maybe       as Myb
import Dict        as Dct


{- SECRET -}

type alias Secret = 
    {
        password  : String,
        password2 : String
    }

type ReleaseMode = Public | Private


{- MODEL -}

type alias Model =
    {
        path           : Path,
        username       : String,
        email          : String,
        websocketReply : String,
        secret         : Secret
    }

default = 
    {
        path           = Pth.LogIn,
        username       = "",
        email          = "",
        websocketReply = "",
        secret         =
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

init : Maybe JsD.Value -> Path -> (Model, Cmd Message)
init flag path = 
    case flag of 
        Just json ->
            (fromJson json, Pth.navigateTo path)
        Nothing ->
            (default, Pth.navigateTo path)


{- JSON ENCODING / DECODING -}

toJson : ReleaseMode -> Model -> JsE.Value
toJson releaseMode model =
    JsE.object
        [   
            ("path"         , JsE.string (Pth.toString model.path)),
            ("username"      , JsE.string model.username             ),
            ("email"         , JsE.string model.email                ),
            ("websocketReply", JsE.string model.websocketReply       ),
            ("secret"        , secretToJson releaseMode model.secret )
        ]

secretToJson : ReleaseMode -> Secret -> JsE.Value
secretToJson releaseMode secret =
    case releaseMode of
        Private ->
            JsE.object
                [
                    ("password" , JsE.string secret.password ),
                    ("password2", JsE.string secret.password2)
                ]
        Public ->
            JsE.object []


fromJson : JsD.Value -> Model
fromJson json =
    let
        decoder =
            JsD.object2 (,)
                (JsD.dict (JsD.maybe JsD.string))
                ("secret" := (JsD.dict JsD.string))

        decodedJson = JsD.decodeValue decoder json
    in
        case decodedJson of
            Ok modelAsTuple ->
                let
                    decodeFst = \s -> fst modelAsTuple |> Dct.get s 
                                                       |> Myb.withDefault Nothing 
                                                       |> Myb.withDefault ""
                    decodeSnd = \s -> snd modelAsTuple |> Dct.get s 
                                                       |> Myb.withDefault "" 
                in
                    Model
                        (Pth.fromString (decodeFst "path"))
                        (decodeFst "username")
                        (decodeFst "email")
                        (decodeFst "websocketReply")
                        (
                            Secret
                                (decodeSnd "password")
                                (decodeSnd "password2")
                        )
            Err error -> default


toJsonWithAction : String -> Model -> String
toJsonWithAction action model =
    JsE.object 
        [
            ("action", JsE.string action),
            ("model", toJson Private model)
        ]
    |> JsE.encode Cfg.jsonIndent
