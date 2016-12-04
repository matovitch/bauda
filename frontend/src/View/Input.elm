module View.Input exposing (..)

import Html.Attributes as HA
import Html.Events     as HE
import Html            as H

import Message       as Msg exposing (Message)
import View.Skeleton as Skl
import Tuple         as Tpl
import Maybe         as Myb
import Dict          as Dct
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
    map |> Dct.map (\_ -> List.map Tpl.first)
        |> Dct.foldl (\_ -> (++)) []
        |> Set.fromList
        |> Set.toList

toMsg : String -> String -> Message
toMsg input =
    Skl.toMsg
        input
        all
        (\s -> Msg.Nothing)
        [
            Msg.Email,
            Msg.Password,
            Msg.Password2,
            Msg.Username
        ]

listOf : String -> List (String, String) -> Skl.HMsg
listOf name items =
    List.map 
        (
            \x->( 
                    [
                        HA.id ("input" ++ (Skl.classify (Tpl.first x))),
                        HA.title (Tpl.first x),
                        HA.type_ (Tpl.second x), 
                        HA.placeholder (Tpl.first x), 
                        HE.onInput (toMsg (Tpl.first x))
                    ], 
                    []
                )
        )
        items
    |> Skl.hList H.form [HA.class name] H.input

oneOf = listOf