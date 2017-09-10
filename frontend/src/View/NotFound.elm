module View.NotFound exposing (view)

import View.Component.Skeleton as C_Skl exposing (skeleton)
import View.Utils              as   Utl
import Model                   as   Mdl exposing (Model)

import Html            as H

view : Model -> Utl.HMsg
view model =
    skeleton model [ H.text "Not Found !" ]