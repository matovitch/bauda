module View.Common.Delete exposing (delete)

import Message as Msg exposing (Message)

import Html            as H  exposing (Html)
import Html.Attributes as HA
import Html.Events     as HE

delete : Message -> Html Message
delete message =
    H.button
        [ 
            HA.class "delete",
            HE.onClick message
        ]
        []