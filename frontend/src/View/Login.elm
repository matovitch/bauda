module View.Login exposing (view)

import View.LogOrSign.Username as LoS_Usn exposing (username)
import View.LogOrSign.Password as LoS_Pwd exposing (password)
import View.LogOrSign.Popup    as LoS_Ppu exposing (popup   )

import View.Common.Skeleton as Cmn_Skl exposing (skeleton)

import Message as Msg exposing (Message)
import Model   as Mdl exposing (Model)

import Html as H exposing (Html)

view : Model -> Html Message
view model =
    skeleton 
        model 
        [ 
            popup
                model
                (
                    username model ++
                    password model
                )
        ]