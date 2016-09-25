module View.Login exposing (view)

import Model       as Mdl exposing (Model)
import Skeleton    as Skt exposing (..)
import View.Button as Btn
import View.Input  as Inp

view : Model -> HMsg
view model =
    skeleton "Login"
        [
            Btn.listOf "LoginOrSigninButtons"  (Btn.get "LoginOrSignin"),
            Inp.listOf "LoginInputs"           (Inp.get "Login"        ),
            Btn.oneOf  "LoginOkButton"         (Btn.get "LoginOk"      )
        ]
