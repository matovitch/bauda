module View.Login exposing (view)

import Model         as Mdl exposing (Model)
import View.Skeleton as Skl exposing (skeleton)
import View.Button   as Btn
import View.Input    as Inp

view : Model -> Skl.HMsg
view model =
    skeleton "Login"
        [
            Btn.listOf "LoginOrSigninButtons"  (Btn.get "LoginOrSignin"),
            Inp.listOf "LoginInputs"           (Inp.get "Login"        ),
            Btn.oneOf  "LoginOkButton"         (Btn.get "LoginOk"      )
        ]
