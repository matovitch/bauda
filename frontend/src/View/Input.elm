module View.Input exposing (..)

import Html.Attributes as HA
import Html.Events     as HE
import Html            as H

import Message  as Msg exposing (Message)
import Skeleton as Skt exposing (HMsg)
import Maybe    as Myb
import Dict     as Dct
import Set

map =
    [
        (
            "Login", 
            [
                ("Username", "text"    ), 
                ("Password", "password")
            ]
        ),
        (
            "SigninOnly", 
            [
                ("Re-enter Password", "password"),
                ("Email"            , "text"    )
            ]
        )
    ] |> Dct.fromList

get : String -> List(String, String)
get s =
    map |> Dct.get s |> Myb.withDefault []

all =
    map |> Dct.map (\_ -> List.map fst)
        |> Dct.foldl (\_ -> (++)) []
        |> Set.fromList
        |> Set.toList

toMsg : String -> String -> Message
toMsg input =
    Skt.toMsg
        input
        all
        (\s -> Msg.Nothing)
        [
            Msg.Email,
            Msg.Password,
            Msg.Password2,
            Msg.Username
        ]

listOf : String -> List (String, String) -> HMsg
listOf name items =
    List.map 
        (
            \x->( 
                    [
                        HA.id ("input" ++ (Skt.classify (fst x))),
                        HA.title (fst x),
                        HA.type' (snd x), 
                        HA.placeholder (fst x), 
                        HE.onInput (toMsg (fst x))
                    ], 
                    []
                )
        )
        items
    |> Skt.hList H.form [HA.class name] H.input

oneOf = listOf