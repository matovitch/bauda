module View.LogOrSign.Username exposing (username)

import Html            as H  exposing (Html)
import Html.Attributes as HA
import Html.Events     as HE

import Message as Msg exposing (Message)
import Model   as Mdl exposing (Model  )

username : Model -> List (Html Message)
username model =
    [
        H.label 
            [ HA.class "label" ]
            [ H.text "Username" ],
        H.p 
            [ HA.class "control has-icons-left" ]
            [ 
                H.input
                    [ 
                        HA.class "input",
                        HA.type_ "text",
                        HA.placeholder "username",
                        HE.onInput Msg.Username,
                        HA.value model.username
                    ]
                    [],
                H.span
                    [ HA.class "icon is-small is-left" ]
                    [ H.i 
                        [ HA.class "fa fa-user" ]
                        []
                    ]
            ]
    ]