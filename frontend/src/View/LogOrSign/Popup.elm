module View.LogOrSign.Popup exposing (popup)

import View.LogOrSign.Buttons as Bts exposing (buttons)
import View.LogOrSign.Utils   as Utl

import View.Common.Delete as Cmn_Dlt exposing (delete)

import Message as Msg exposing (Message)
import Model   as Mdl exposing (Model)

import Html            as H  exposing (Html)
import Html.Attributes as HA
import Html.Events     as HE

popup : Model -> List (Html Message) -> Html Message
popup model controls =
    H.div 
        [ HA.class "modal is-active" ]
        [
            H.div
                [ HA.class "modal-background" ]
                [],
            H.div
                [ HA.class "modal-card", HA.style [ ("max-width", "25em") ] ]
                [
                    H.header
                        [ HA.class "modal-card-head" ]
                        [ 
                            H.p
                                [ HA.class "modal-card-title" ]
                                [ Utl.logOrSign model ],
                            delete (Msg.Back 1)
                        ],
                    H.section
                        [ HA.class "modal-card-body" ]
                        [ H.div 
                            [ HA.class "field" ]
                            controls 
                        ],
                    H.footer
                        [ HA.class "modal-card-foot" ]
                        [ buttons model ]
                ]
        ]

