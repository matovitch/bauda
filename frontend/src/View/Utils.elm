module View.Utils exposing (..)

import Message         as Msg exposing (Message)
import Html.Attributes as HA
import Html            as H

type alias HMsg = H.Html Message
type alias HAtt = H.Attribute Message
type alias HTag = List HAtt -> List HMsg -> HMsg

hList : HTag -> List HAtt -> HTag -> List(List HAtt, List HMsg) -> HMsg
hList hGTag globals hLTag items =
    hGTag globals (List.map (uncurry hLTag) items)