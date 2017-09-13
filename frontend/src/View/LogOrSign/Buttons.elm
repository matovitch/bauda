module View.LogOrSign.Buttons exposing (buttons)

import View.LogOrSign.Utils as Utl

import Message as Msg exposing (Message)
import Model   as Mdl exposing (Model  )
import Query   as Qry exposing (Query  )
import Path    as Pth

import Html            as H  exposing (Html)
import Html.Attributes as HA
import Html.Events     as HE

import String as Str
import Regex  as Rgx

cancel : Html Message
cancel =
    H.p 
        [ HA.class "control" ]
        [ H.a
            [ 
                HA.class "button",
                HE.onClick (Msg.Back 1)
            ]
            [ 
                H.p [] [ H.text "Cancel" ],
                H.span
                        [ HA.class "icon" ]
                        [ H.i 
                            [ HA.class "fa fa-times" ]
                            []
                        ]
            ]
        ]

button : Model -> Html Message
button model =
    let
        onClick =
            case model.path of
                Pth.SignIn -> [ HE.onClick (Msg.ServerQuery Qry.SignIn) ]
                Pth.LogIn  -> [ HE.onClick (Msg.ServerQuery Qry.LogIn ) ]
                _          -> []

        isLoading =
            if model.is_waiting_server
            then
                [ HA.class "is-loading" ]
            else
                []

        isEnabled =
                ( 
                    model.path == Pth.LogIn &&
                    not (Str.isEmpty model.secret.password)
                ) 
            ||
                (
                    model.path == Pth.SignIn  &&
                    Utl.isPasswordValid model &&
                    Utl.isEmailValid    model
                )
            && 
                not (Str.isEmpty model.username)

        title =
            if Str.isEmpty model.username || 
               Str.isEmpty model.secret.password
            then
                "Some fields are missing."
            else
                ""
    in
        H.p 
            [ HA.class "control" ]
            [ H.button
                (
                    [ 
                        HA.class "button is-primary",
                        HA.disabled (not isEnabled),
                        HA.title title
                    ]         ++
                    isLoading ++
                    onClick
                )
                [
                    H.span
                        [ HA.class "icon" ]
                        [ H.i 
                            [ HA.class "fa fa-sign-in" ]
                            []
                        ],
                    H.p [] [ H.text (Utl.logOrSign model) ]
                ]
                 
            ]

buttons : Model -> Html Message
buttons model =
    H.div 
        [ HA.class "field is-grouped" ]
        [ 
            button model,
            cancel
        ]