module View.Component.Footer exposing (footer)

import View.Utils      as Utl

import Html.Attributes as HA
import Html            as H

import Model           as Mdl exposing (Model)

footer : Model -> Utl.HMsg
footer model =

        H.div 
            [ HA.class "container" ]
            [ H.div
                [ HA.class "content has-text-centered" ]
                [ 
                    H.hr [] [],
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
        