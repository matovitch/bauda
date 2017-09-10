module View.Common.Skeleton exposing (skeleton)

import Message as Msg exposing (Message)
import Model   as Mdl exposing (Model  )
import Path    as Pth exposing (Path   )

import Html            as H  exposing (Html)
import Html.Attributes as HA
import Html.Events     as HE

brand : Model -> Html Message
brand model =
    H.h1 
        [ 
            HA.class "title",
            HE.onClick (Msg.GotoPath Pth.Home)
        ]
        [ H.text   "Bauda" ]

logButtons : Model -> Html Message
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


header : Model -> Html Message
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

footer : Model -> Html Message
footer model =
        H.div 
            [ HA.class "container" ]
            [ H.div
                [ HA.class "content has-text-centered" ]
                [ 
                    H.hr [ HA.style [ ("margin", "0") ] ] [],
                    H.p 
                        []
                        [ 
                            H.text "This page is ", 
                            H.b 
                                [] 
                                [ H.text "open source" ],
                            H.text ". Noticed a typo? Or something unclear? ",
                            H.a 
                                [ HA.href "https://github.com/matovitch/bauda" ] 
                                [ H.text "Improve this page on Github." ]
                        ]
                ]
            ]

skeleton : Model -> List (Html Message) -> Html Message
skeleton model listHtmlMessages =
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
                    [ H.div 
                        [ HA.class "container" ]
                        listHtmlMessages
                    ],
                H.div 
                    [ HA.class "hero-footer" ]
                    [ footer model ]
            ]
    ]