module Update exposing (update)

import Message as Msg exposing (Message)
import Query   as Qry exposing (Query  )
import Model   as Mdl exposing (Model  )
import Path    as Pth exposing (Path   )
import Server  as Srv

update : Message -> Model -> (Model, Cmd Message)
update msg model = 
    let
        ask = \query -> Srv.send (Mdl.buildQuery model query)

        {-Use intermediary expression because of https://github.com/elm-lang/elm-compiler/issues/537-}
        secret            = model.secret
        is_burger_active  = model.is_burger_active
    in
        case msg of
            Msg.ChangePath  path  -> ({ model | path     = path                          }, Cmd.none             )
            Msg.Username    text  -> ({ model | username = text                          }, Cmd.none             )
            Msg.Email       text  -> ({ model | email    = text                          }, Cmd.none             )
            Msg.Password    text  -> ({ model | secret   = {secret | password  = text}   }, Cmd.none             )
            Msg.Password2   text  -> ({ model | secret   = {secret | password2 = text}   }, Cmd.none             )
            Msg.ServerQuery query -> ({ model | is_waiting_server = True                 }, ask query            )
            Msg.ServerReply reply -> ({ model | is_waiting_server = False                }, Cmd.none             )
            Msg.Timeout     time  -> ({ model | is_waiting_server = False                }, Pth.goto Pth.NotFound)
            Msg.ClickBurger       -> ({ model | is_burger_active  = not is_burger_active }, Cmd.none             )
            Msg.GotoPath    path  -> (  model                                             , Pth.goto path        )
            Msg.Back        steps -> (  model                                             , Pth.back steps       )