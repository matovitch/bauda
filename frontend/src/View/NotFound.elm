module View.NotFound exposing (view)

import View.Common.Skeleton as Cmn_Skl exposing (skeleton)

import Message as Msg exposing (Message)
import Model   as Mdl exposing (Model  )

import Html as H exposing (Html)

view : Model -> Html Message
view model =
    skeleton model [ H.text "Not Found !" ]