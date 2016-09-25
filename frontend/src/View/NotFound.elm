module View.NotFound exposing (..)

import Model    as Mdl exposing (Model)
import Skeleton as Skt exposing (..)
import Html     as H

view : Model -> HMsg
view model =
    skeleton "NotFound" [H.text "Not Found !"]