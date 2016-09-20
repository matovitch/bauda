module Update exposing (update)

import WebSocket as WSk
import Message   as Msg
import Model     as Mdl
import Config    as Cfg

update : Msg.Message -> Mdl.Model -> (Mdl.Model, Cmd Msg.Message)
update msg model = 
    let 
        updated =
            case msg of
                Msg.GotoLogIn            -> ({ model | logInOrSignIn   = Mdl.LogIn }, Cmd.none)
                Msg.GotoSignIn           -> ({ model | logInOrSignIn   = Mdl.SignIn}, Cmd.none)
                Msg.Username        text -> ({ model | username        = text }     , Cmd.none)
                Msg.Password        text -> ({ model | password        = text }     , Cmd.none)
                Msg.ReEnterPassword text -> ({ model | reEnterPassword = text }     , Cmd.none)
                Msg.Email           text -> ({ model | email           = text }     , Cmd.none)
                Msg.RunLogIn             -> (
                                                model,
                                                WSk.send Cfg.websocketServer (Mdl.toJsonWithAction "login" model)
                                            )
                Msg.RunSignIn             -> (
                                                model,
                                                WSk.send Cfg.websocketServer (Mdl.toJsonWithAction "signin" model)
                                            )
                Msg.WebsocketReply  text -> ({ model | websocketReply = text }      , Cmd.none)
                _                        -> (model                                  , Cmd.none)
    in
        Mdl.store updated