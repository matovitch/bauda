module View.Button exposing (..)

import Html.Attributes as HA
import Html.Events     as HE
import Html            as H

import Message  as Msg exposing (Message)
import Skeleton as Skt exposing (HMsg)
import Maybe    as Myb
import Dict     as Dct
import Path     as Pth
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

toMsg : String -> Msg.Message
toMsg button =
    Skt.toMsg
        button
        all
        Msg.Nothing
        [
            Msg.ToPath Pth.LogIn, 
            Msg.RunLogIn,
            Msg.ToPath Pth.SignIn,
            Msg.RunSignIn
        ]

listOf: String -> List String -> HMsg
listOf name list =
    List.map 
        (
            \x->
                (
                    [
                        HA.title x, 
                        HE.onClick (toMsg x),
                        HA.id ("button" ++ (Skt.classify x))
                    ],
                    [
                        H.text x
                    ]
                )
        )
        list
    |> Skt.hList H.div [HA.class name] H.button

oneOf = listOf