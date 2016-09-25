module View.Home exposing (view)

import Model    as Mdl exposing (Model)
import Skeleton as Skt exposing (..)
import Html     as H

view : Model -> HMsg
view =
    (\_ -> skeleton "Home" [H.text "Home !"])