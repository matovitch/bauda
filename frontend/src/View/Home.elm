module View.Home exposing (view)

import View.Skeleton as Skl exposing (skeleton)
import Model         as Mdl exposing (Model)
import Html          as H

view : Model -> Skl.HMsg
view model =
    skeleton "Home" [H.text "Home !"]