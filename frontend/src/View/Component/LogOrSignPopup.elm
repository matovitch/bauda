module View.Component.LogOrSignPopup exposing (logOrSignPopup)

import View.Utils      as Utl

import Html.Attributes as HA
import Html.Events     as HE
import Html            as H

import Message         as Msg exposing (Message)
import Model           as Mdl exposing (Model)
import Query           as Qry exposing (Query)
import Path            as Pth

import Maybe           as Myb


logOrSign : Model -> Utl.HMsg
logOrSign model =
    H.text
        (
            case model.path of
                Pth.SignIn -> "Sign in"
                Pth.LogIn  -> "Log in"
                _          -> ""
        )

delete : Utl.HMsg
delete =
    H.button
        [ 
            HA.class "delete",
            HE.onClick Msg.Back
        ]
        []

cancel : Utl.HMsg
cancel =
    H.p 
        [ HA.class "control" ]
        [ H.a
            [ 
                HA.class "button",
                HE.onClick Msg.Back
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

button : Model -> Utl.HMsg
button model =
    let
        onClick =
            case model.path of
                Pth.SignIn -> [ HE.onClick (Msg.ServerQuery Qry.SignIn) ]
                Pth.LogIn  -> [ HE.onClick (Msg.ServerQuery Qry.LogIn ) ]
                _          -> []
    in
        H.p 
            [ HA.class "control" ]
            [ H.button
                (
                    [ HA.class "button is-primary" ] ++
                    onClick
                )
                [
                    H.span
                        [ HA.class "icon" ]
                        [ H.i 
                            [ HA.class "fa fa-sign-in" ]
                            []
                        ],
                    H.p [] [ logOrSign model ]
                ]
                 
            ]

buttons : Model -> Utl.HMsg
buttons model =
    H.div 
        [ HA.class "field is-grouped" ]
        [ 
            button model,
            cancel
        ]


username : List Utl.HMsg
username =
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
                        HE.onInput Msg.Username
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

email : List Utl.HMsg
email =
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
                        HE.onInput Msg.Email
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

password : List Utl.HMsg
password =
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
                        HE.onInput Msg.Password
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

password2 : List Utl.HMsg
password2 =
    [
        H.br [] [],
        H.p 
            [ HA.class "control has-icons-left" ]
            [ 
                H.input
                    [ 
                        HA.class "input",
                        HA.type_ "password",
                        HA.placeholder "password (confirmation)",
                        HE.onInput Msg.Password2
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

field : Model -> Utl.HMsg
field model =
    let
        controls =
            case model.path of
                Pth.SignIn -> (email ++ username ++ password ++ password2)
                Pth.LogIn  -> (username ++ password)
                _          -> []
    in
        H.div 
        [ HA.class "field" ]
        controls

logOrSignPopup : Model -> Utl.HMsg
logOrSignPopup model =
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
                                [ logOrSign model ],
                            delete
                        ],
                    H.section
                        [ HA.class "modal-card-body" ]
                        [ field model ],
                    H.footer
                        [ HA.class "modal-card-foot" ]
                        [ buttons model ]
                ]
        ]