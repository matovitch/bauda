module View.NotFound exposing (view)

import View.Skeleton as Skl exposing (skeleton)
import Model         as Mdl exposing (Model)
import Html          as H

view : Model -> Skl.HMsg
view model =
    skeleton "NotFound" [H.text "Not Found !"]