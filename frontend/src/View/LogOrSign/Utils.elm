module View.LogOrSign.Utils exposing (..)

import Message as Msg exposing (Message)
import Model   as Mdl exposing (Model  )
import Path    as Pth exposing (Path   )
import Config  as Cfg

import Html   as H exposing (Html)
import String as Str

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

logOrSign : Model -> Html Message
logOrSign model =
    H.text
        (
            case model.path of
                Pth.SignIn -> "Sign in"
                Pth.LogIn  -> "Log in"
                _          -> ""
        )