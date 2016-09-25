module View.Signin exposing (view)

import Model       as Mdl exposing (Model)
import Skeleton    as Skt exposing (..)
import View.Button as Btn
import View.Input  as Inp

view : Model -> HMsg
view model =
    skeleton "Signin"
        [
            Btn.listOf "SigninButtons"  (Btn.get "signin"  ),
            Inp.listOf "SigninInputs"   (Inp.get "signin"  ),
            Btn.oneOf  "SigninOkButton" (Btn.get "signinOk")
        ]