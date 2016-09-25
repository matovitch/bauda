module View.Signin exposing (view)

import Model       as Mdl exposing (Model)
import Skeleton    as Skt exposing (..)
import View.Button as Btn
import View.Input  as Inp

view : Model -> HMsg
view model =
    skeleton "Signin"
        [
            Btn.listOf "LoginOrSigninButtons"  (Btn.get "LoginOrSignin"),
            Inp.listOf "LoginInputs"           (Inp.get "Login"        ),
            Inp.listOf "SigninOnlyInputs"      (Inp.get "SigninOnly"   ),
            Btn.oneOf  "SigninOkButton"        (Btn.get "SigninOk"     )
        ]