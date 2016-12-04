module View.Button exposing (..)

import Html.Attributes as HA
import Html.Events     as HE
import Html            as H

import Message       as Msg exposing (Message)
import View.Skeleton as Skl
import Query         as Qry
import Maybe         as Myb
import Dict          as Dct
import Path          as Pth
import Set

map =
    [
        (
            "LoginOrSignin", 
            [
                "Log In",
                "Sign In"
            ]
        ),
        (
            "LoginOk", 
            [
                "Log In !"
            ]
        ),
        (
            "SigninOk", 
            [
                "Sign In !"
            ]
        )
    ] |> Dct.fromList

get : String -> List String
get s =
    map |> Dct.get s |> Myb.withDefault []

all =
    map |> Dct.foldl (\_ -> (++)) []
        |> Set.fromList
        |> Set.toList

toMsg : String -> Message
toMsg button =
    Skl.toMsg
        button
        all
        Msg.Nothing
        [
            Msg.GotoPath    Pth.LogIn, 
            Msg.ServerQuery Qry.LogIn,
            Msg.GotoPath    Pth.SignIn,
            Msg.ServerQuery Qry.SignIn
        ]

listOf: String -> List String -> Skl.HMsg
listOf name list =
    List.map 
        (
            \x->
                (
                    [
                        HA.title x, 
                        HE.onClick (toMsg x),
                        HA.id ("button" ++ (Skl.classify x))
                    ],
                    [
                        H.text x
                    ]
                )
        )
        list
    |> Skl.hList H.div [HA.class name] H.button

oneOf = listOf