port module Model exposing (..)

import Json.Decode as JsD exposing ((:=))
import Json.Encode as JsE
import Message     as Msg
import Config      as Cfg
import Maybe
import Dict

type State = LogIn | SignIn

type alias Model =
    {
        state          : State,
        username       : String,
        password       : String,
        password2      : String,
        email          : String,
        websocketReply : String
    }

default = Model LogIn "" "" "" "" ""

init : Maybe JsD.Value -> (Model, Cmd Msg.Message)
init flag = 
    (
        case flag of 
            Just json ->
                fromJson json
            Nothing ->
                default,
        Cmd.none
    )

toJson : Model -> JsE.Value
toJson model =
    JsE.object
        [   
            (
                "state",
                case model.state of
                    LogIn  -> JsE.string "Log In"
                    SignIn -> JsE.string "Sign In"
            ),
            ("username"      , JsE.string model.username      ),
            ("password"      , JsE.string model.password      ),
            ("password2"     , JsE.string model.password2     ),
            ("email"         , JsE.string model.email         ),
            ("websocketReply", JsE.string model.websocketReply)
        ]


fromJson : JsD.Value -> Model
fromJson json =
    let
        decodedJson = JsD.decodeValue (JsD.dict JsD.string) json
    in
        case decodedJson of
            Ok modelAsTuple ->
                let
                    decodeString = \s -> modelAsTuple |> Dict.get s |> Maybe.withDefault ""
                in
                    Model
                        (
                            case (decodeString "state") of
                                "Sign In" -> SignIn
                                _ -> LogIn
                        )
                        (decodeString "username")
                        (decodeString "password")
                        (decodeString "password2")
                        (decodeString "email")
                        (decodeString "websocketReply")
            _ -> 
                default


toJsonWithAction : String -> Model -> String
toJsonWithAction action model =
    JsE.object 
        [
            ("action", JsE.string action),
            ("model", toJson model)
        ]
    |> JsE.encode Cfg.jsonIndent

port setStorage : JsD.Value -> Cmd msg

store : (Model, Cmd Msg.Message) -> (Model, Cmd Msg.Message)
store (model, cmd) = 
    (model, Cmd.batch [setStorage (toJson model), cmd])