module View.ForgotPassword exposing (view)

import View.Common.Skeleton  as Cmn_Skl exposing (skeleton)
import View.Common.Delete as Cmn_Dlt exposing (delete)

import View.Utils as   Utl

import Message as Msg exposing (Message)
import Model   as Mdl exposing (Model)

import Html.Attributes as HA
import Html            as H

view : Model -> Utl.HMsg
view model =
    skeleton 
        model 
        [ 
            H.div 
                [ HA.class "modal is-active" ]
                [
                    H.div
                        [ HA.class "modal-background" ]
                        [],
                    H.div
                        [ HA.class "modal-card" ]
                        [
                            H.header
                                [ HA.class "modal-card-head" ]
                                [ 
                                    H.p
                                        [ HA.class "modal-card-title" ]
                                        [ H.text   "Password reset" ],
                                    delete (Msg.Back 2)
                                ],
                            H.section
                                [ HA.class "modal-card-body" ]
                                [ H.p 
                                    [] 
                                    [ H.text "You should receive a mail allowing you to reset your password in a few moments." ] 
                                ]
                        ]
                ]
        ]