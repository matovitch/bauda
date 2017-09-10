module View.Login exposing (view)

import View.Component.LogOrSignPopup as C_LSP exposing (logOrSignPopup)
import View.Component.Skeleton       as C_Skl exposing (skeleton)
import View.Utils                    as   Utl
import Model                         as   Mdl exposing (Model)

view : Model -> Utl.HMsg
view model =
    skeleton model [ logOrSignPopup model ]