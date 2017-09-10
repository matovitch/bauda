module View.LogOrSign.Password2 exposing (password2)

import View.LogOrSign.Utils as Utl

import Message as Msg exposing (Message)
import Model   as Mdl exposing (Model  )
import Config  as Cfg

import Html            as H  exposing (Html)
import Html.Attributes as HA
import Html.Events     as HE

import String as Str

type alias Annotations = 
    {
        icon   : String,
        color  : String,
        helper : String
    }

password2 : Model -> List (Html Message)
password2 model =
    let
        annotations = 
            if Str.isEmpty model.secret.password
            then
                {
                    icon   = "lock",
                    color  = "",
                    helper = "" 
                }
            else
                if  ( Utl.arePasswordsMatching model &&
                      Utl.isPasswordLongEnough model )
                then
                    {
                        icon   = "check",
                        color  = "is-success",
                        helper = "" 
                    }
                else
                    if not (Utl.arePasswordsMatching model)
                    then
                        {
                            icon   = "times",
                            color  = "is-danger",
                            helper = "The passwords do not match." 
                        }
                    else
                        if not (Utl.isPasswordLongEnough model)
                        then
                            {
                                icon   = "times",
                                color  = "is-danger",
                                helper = "The password is not long enough (" ++
                                          toString Cfg.minPasswordLength ++
                                         " characters min.)"
                            }
                        else
                            {
                                icon   = "lock",
                                color  = "",
                                helper = "" 
                            }
        help = 
            if Str.isEmpty annotations.helper
            then
                []
            else
                [ H.p
                    [ HA.class "help is-danger" ]
                    [ H.text annotations.helper ]
                ]
    in
    [
        H.p 
            [ 
                HA.class "control has-icons-left",
                HA.style [ ("margin-top", "0.3em") ]  
            ]
            [ 
                H.input
                    [ 
                        HA.class "input",
                        HA.class annotations.color,
                        HA.type_ "password",
                        HA.placeholder "password (confirmation)",
                        HE.onInput Msg.Password2,
                        HA.value model.secret.password2
                    ]
                    [],
                H.span
                    [ HA.class "icon is-small is-left" ]
                    [ H.i 
                        [ HA.class ("fa fa-" ++ annotations.icon) ]
                        []
                    ]
            ]
    ] ++ help
