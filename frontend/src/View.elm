module View exposing (view)

import View.ForgotPassword as ForgotPassword
import View.NotFound       as NotFound
import View.Signin         as Signin
import View.Login          as Login
import View.Home           as Home

import Message as Msg exposing (Message)
import Model   as Mdl exposing (Model  )
import Path    as Pth

import Html as H exposing (Html)

view : Model -> Html Message
view model =
    case model.path of
        Pth.Home           ->           Home.view model
        Pth.LogIn          ->          Login.view model
        Pth.SignIn         ->         Signin.view model
        Pth.ForgotPassword -> ForgotPassword.view model
        _                  ->       NotFound.view model