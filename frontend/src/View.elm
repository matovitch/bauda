module View exposing (view)

import Model         as Mdl exposing (Model)
import View.NotFound as NotFound
import View.Signin   as Signin
import View.Login    as Login
import View.Home     as Home
import View.Skeleton as Skt
import Path          as Pth

view : Model -> Skt.HMsg
view model =
    case model.path of
        Pth.Home   ->     Home.view model
        Pth.LogIn  ->    Login.view model
        Pth.SignIn ->   Signin.view model
        _          -> NotFound.view model