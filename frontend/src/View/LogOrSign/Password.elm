module View.LogOrSign.Password exposing (password)

import Message as Msg exposing (Message)
import Model   as Mdl exposing (Model  )
import Path    as Pth

import Html            as H  exposing (Html)
import Html.Attributes as HA
import Html.Events     as HE

password : Model -> List (Html Message)
password model =
    [
        H.label 
            [ HA.class "label" ]
            [ H.text "Password" ],
        H.p 
            [ HA.class "control has-icons-left" ]
            [ 
                H.input
                    [ 
                        HA.class "input",
                        HA.type_ "password",
                        HA.placeholder "password",
                        HE.onInput Msg.Password,
                        HA.value model.secret.password
                    ]
                    [],
                H.span
                    [ HA.class "icon is-small is-left" ]
                    [ H.i 
                        [ HA.class "fa fa-lock" ]
                        []
                    ]
            ]
    ]
    ++
    (
        case model.path of
            Pth.LogIn ->
                [ H.a
                    [ 
                        HA.class "help",
                        HE.onClick (Msg.GotoPath Pth.ForgotPassword)
                    ]
                    [ H.text "I forgot my password." ]
                ]
            _ -> 
                []
    )