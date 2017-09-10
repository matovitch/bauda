module View.Component.Body exposing (body)

import View.Utils      as Utl

import Html.Attributes as HA
import Html            as H

import Model           as Mdl exposing (Model)

body : Model -> List Utl.HMsg -> Utl.HMsg
body model hMsgList =
    H.div 
        [ HA.class "container" ]
        hMsgList