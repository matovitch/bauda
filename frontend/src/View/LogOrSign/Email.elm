module View.LogOrSign.Email exposing (email)

import View.LogOrSign.Utils as Utl

import Message as Msg exposing (Message)
import Model   as Mdl exposing (Model  )

import Html            as H  exposing (Html)
import Html.Attributes as HA
import Html.Events     as HE

import String as Str

email : Model -> List (Html Message)
email model =
    let
        annotation = 
            if Str.isEmpty model.email
            then
                {
                    icon  = "envelope",
                    color = "",
                    help  = "" 
                }
            else
                if Utl.isEmailValid model
                then
                    {
                        icon  = "check",
                        color = "is-success",
                        help  = "The email adress is valid!"
                    }
                else
                    {
                        icon  = "times",
                        color = "is-danger",
                        help  = "This email address is not valid."
                    }

        help = Utl.craftHelp annotation
    in
            
    [
        H.label 
            [ HA.class "label" ]
            [ H.text "Email" ],
        H.p 
            [ 
                HA.class "control has-icons-left"
            ]
            [ 
                H.input
                    [ 
                        HA.class "input",
                        HA.type_ "text",
                        HA.placeholder "email",
                        HE.onInput Msg.Email,
                        HA.value model.email,
                        HA.class annotation.color
                    ]
                    [],
                H.span
                    [ HA.class "icon is-small is-left" ]
                    [ H.i 
                        [ HA.class ("fa fa-" ++ annotation.icon) ]
                        []
                    ]
            ]
    ] ++ help