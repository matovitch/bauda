module View.Component.Header exposing (header)

import View.Utils                as Utl

import Html.Attributes as HA
import Html.Events     as HE
import Html            as H

import Message         as Msg exposing (Message)
import Model           as Mdl exposing (Model)
import Path            as Pth

brand : Model -> Utl.HMsg
brand model =
    H.h1 
        [ 
            HA.class "title",
            HE.onClick (Msg.GotoPath Pth.Home)
        ]
        [ H.text   "Bauda" ]

logButtons : Model -> Utl.HMsg
logButtons model =
    H.div 
        [ HA.class "field is-grouped is-grouped-right" ]
        [ 
            H.p 
                [ HA.class "control" ]
                [ H.a
                    [ 
                        HA.class "button",
                        HE.onClick (Msg.GotoPath Pth.LogIn)
                    ]
                    [ H.text "Log in" ]
                ],
            H.p 
                [ HA.class "control" ]
                [ H.a
                    [ 
                        HA.class "button is-info",
                        HE.onClick (Msg.GotoPath Pth.SignIn)
                    ]
                    [ H.text "Sign in" ]
                ]
        ]


header : Model -> Utl.HMsg
header model =
    let
        isBurgerActiveAsString =
            if model.is_burger_active then
                "is-active"
            else
                ""
    in
        H.div
            [ HA.class "container is-widescreen" ]
            [ 
                H.div
                    [ HA.class "container" ]
                    [ H.div 
                        [ HA.class "navbar" ]
                        [
                            H.div
                                [ HA.class "navbar-brand" ]
                                [ 
                                    H.div
                                        [ HA.class "navbar-item" ]
                                        [ brand model ],
                                    H.div
                                        [ 
                                            HA.class "navbar-burger",
                                            HA.class isBurgerActiveAsString,
                                            HE.onClick Msg.ClickBurger
                                        ]
                                        [
                                            H.span [] [],
                                            H.span [] [],
                                            H.span [] []
                                        ]
                                ],
                            H.div
                                [ 
                                    HA.class "navbar-menu",
                                    HA.class isBurgerActiveAsString,
                                    HA.id "navMenu"
                                ]
                                [ H.div
                                    [ HA.class "navbar-end" ]
                                    [ H.div
                                        [ HA.class "navbar-item" ]
                                        [ logButtons model ]
                                    ]
                                ]
                        ]
                    ],
                H.hr [ HA.style [ ("margin", "0") ] ] []
            ]