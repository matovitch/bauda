module View.Component.Skeleton exposing (skeleton)

import View.Component.Header as Hdr exposing (header)
import View.Component.Footer as Ftr exposing (footer)
import View.Component.Body   as Bdy exposing (body)
import View.Utils            as Utl

import Html.Attributes as HA
import Html            as H

import Model as Mdl exposing (Model)

skeleton : Model -> List Utl.HMsg -> Utl.HMsg
skeleton model hMsgList =
    H.div []
    [
        H.section
            [ HA.class "hero is-fullheight" ]
            [
                H.div 
                    [ HA.class "hero-head" ]
                    [ header model ],
                H.div 
                    [ HA.class "hero-body" ]
                    [ body model hMsgList ],
                H.div 
                    [ HA.class "hero-footer" ]
                    [ footer model ]
            ]
    ]