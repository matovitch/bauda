module Update exposing (update)

import WebSocket as WSk
import Message   as Msg
import Model     as Mdl
import Config    as Cfg

update : Msg.Message -> Mdl.Model -> (Mdl.Model, Cmd Msg.Message)
update msg model = 
    let
        requestAction = \action ->  WSk.send Cfg.websocketServer (Mdl.toJsonWithAction action model)
        updated =
            case msg of
                Msg.GotoLogIn            -> ({ model | state     = Mdl.LogIn }, Cmd.none              )
                Msg.GotoSignIn           -> ({ model | state     = Mdl.SignIn}, Cmd.none              )
                Msg.Username        text -> ({ model | username       = text }, Cmd.none              )
                Msg.Password        text -> ({ model | password       = text }, Cmd.none              )
                Msg.Password2       text -> ({ model | password2      = text }, Cmd.none              )
                Msg.Email           text -> ({ model | email          = text }, Cmd.none              )
                Msg.WebsocketReply  text -> ({ model | websocketReply = text }, Cmd.none              )
                Msg.RunLogIn             -> (  model                          , requestAction  "login")
                Msg.RunSignIn            -> (  model                          , requestAction "signin")
                _                        -> (  model                          , Cmd.none              )
    in
        Mdl.store updated