module View.LogOrSign.Utils exposing (..)

import Message as Msg exposing (Message)
import Model   as Mdl exposing (Model  )
import Path    as Pth exposing (Path   )
import Config  as Cfg

import Html            as H  exposing (Html)
import Html.Attributes as HA

import String as Str
import Regex  as Rgx

type alias Annotation =
    {
        icon  : String,
        color : String,
        help  : String
    }

craftHelp : Annotation -> List (Html Message)
craftHelp annotation =
    if not (Str.isEmpty annotation.help)
    then
        [ H.p
            [ 
                HA.class "help",
                HA.class annotation.color
            ]
            [ H.text annotation.help ]
        ]
    else
        []

arePasswordsMatching : Model -> Bool
arePasswordsMatching model =
    model.secret.password ==
    model.secret.password2

isPasswordLongEnough : Model -> Bool
isPasswordLongEnough model =
    Str.length model.secret.password > Cfg.minPasswordLength

isPasswordValid : Model -> Bool
isPasswordValid model =
    arePasswordsMatching model &&
    isPasswordLongEnough model

isEmailValid : Model -> Bool
isEmailValid model =
    let
        emailRegex = Rgx.regex Cfg.emailRegex
    in
        Rgx.contains emailRegex model.email

logOrSign : Model -> Html Message
logOrSign model =
    H.text
        (
            case model.path of
                Pth.SignIn -> "Sign in"
                Pth.LogIn  -> "Log in"
                _          -> ""
        )