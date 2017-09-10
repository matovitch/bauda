module View.LogOrSign.Email exposing (email)

import Html            as H  exposing (Html)
import Html.Attributes as HA
import Html.Events     as HE

import Message as Msg exposing (Message)
import Model   as Mdl exposing (Model  )

email : Model -> List (Html Message)
email model =
    [
        H.label 
            [ HA.class "label" ]
            [ H.text "Email" ],
        H.p 
            [ HA.class "control has-icons-left" ]
            [ 
                H.input
                    [ 
                        HA.class "input",
                        HA.type_ "text",
                        HA.placeholder "email",
                        HE.onInput Msg.Email,
                        HA.value model.email
                    ]
                    [],
                H.span
                    [ HA.class "icon is-small is-left" ]
                    [ H.i 
                        [ HA.class "fa fa-envelope" ]
                        []
                    ]
            ]
    ]