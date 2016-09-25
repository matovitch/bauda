module View.Login exposing (view)

import Model             as Mdl exposing (Model)
import Skeleton          as Skt exposing (..)
import View.Button            as Btn
import View.Input             as Inp

view : Model -> HMsg
view model =
    skeleton "Login"
        [
            Btn.listOf "LoginButtons"  (Btn.get "login"  ),
            Inp.listOf "LoginInputs"   (Inp.get "login"  ),
            Btn.oneOf  "LoginOkButton" (Btn.get "loginOk")
        ]
