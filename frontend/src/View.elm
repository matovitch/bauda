module View exposing (view)

import Model         as Mdl exposing (Model)
import Skeleton      as Skt exposing (HMsg)
import Path          as Pth

{-Views-}
import View.NotFound as NotFound
import View.Signin   as Signin
import View.Login    as Login
import View.Home     as Home

view : Model -> HMsg
view model =
    case model.path of
        Pth.Home   ->     Home.view model
        Pth.LogIn  ->    Login.view model
        Pth.SignIn ->   Signin.view model
        _          -> NotFound.view model