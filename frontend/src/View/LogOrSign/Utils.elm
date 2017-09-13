module View.LogOrSign.Utils exposing (..)

import Message as Msg exposing (Message)
import Model   as Mdl exposing (Model  )
import Path    as Pth exposing (Path   )
import Config  as Cfg

import Html            as H  exposing (Html)
import Html.Attributes as HA

import String as Str
import Regex  as Rgx

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

logOrSign : Model -> String
logOrSign model =
    case model.path of
        Pth.SignIn -> "Sign in"
        Pth.LogIn  -> "Log in"
        _          -> ""