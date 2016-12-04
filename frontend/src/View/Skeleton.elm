module View.Skeleton exposing (..)

import Message         as Msg exposing (Message)
import Html.Attributes as HA
import Html            as H
import Maybe           as Myb
import Dict            as Dct
import Regex           as Rgx


type alias HMsg = H.Html Message
type alias HAtt = H.Attribute Message
type alias HTag = List HAtt -> List HMsg -> HMsg

hList : HTag -> List HAtt -> HTag -> List(List HAtt, List HMsg) -> HMsg
hList hGTag globals hLTag items =
    hGTag globals (List.map (uncurry hLTag) items)

skeleton : String -> List HMsg -> HMsg
skeleton className hMsgList =
    H.div [HA.class className] hMsgList

toMsg : String -> List String -> a -> List a -> a
toMsg key keys msg msgs =
    List.map2 (,)
        keys
        msgs
    |> Dct.fromList
    |> Dct.get key
    |> Myb.withDefault msg

classify : String -> String
classify s =
    Rgx.replace Rgx.All (Rgx.regex "[^(a-z|A-Z|0-9)]") (\_ -> "_") s