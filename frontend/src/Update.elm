module Update exposing (update, urlUpdate)

import Message     as Msg exposing (Message)
import Model       as Mdl exposing (Model)
import Maybe       as Myb exposing (Maybe)
import Path        as Pth exposing (Path)
import Json.Decode as JsD
import WebSocket   as WSk
import Config      as Cfg


update : Message -> Model -> (Model, Cmd Message)
update msg model = 
    let
        requestAction = \action ->  WSk.send Cfg.websocketServer (Mdl.toJsonWithAction action model)

        {-Use intermediary expression because of https://github.com/elm-lang/elm-compiler/issues/537-}
        secret = model.secret
    in
        case msg of
            Msg.ToPath          path -> ( model                                             , Pth.navigateTo path   )
            Msg.Username        text -> ({model | username                     = text      }, Cmd.none              )
            Msg.Email           text -> ({model | email                        = text      }, Cmd.none              )
            Msg.Password        text -> ({model | secret = {secret | password  = text}     }, Cmd.none              )
            Msg.Password2       text -> ({model | secret = {secret | password2 = text}     }, Cmd.none              )
            Msg.RunLogIn             -> ( model                                             , requestAction  "login")
            Msg.RunSignIn            -> ( model                                             , requestAction "signin")
            Msg.WebsocketReply  text -> ( model                                             , Cmd.none              )            
            _                        -> ( model                                             , Cmd.none              )

urlUpdate : Path -> Model -> (Model, Cmd Message)
urlUpdate path model =
    let
        model = {model | path = path}
    in 
        case path of
            Pth.Home   -> (model, Cmd.none)
            Pth.LogIn  -> (model, Cmd.none)
            Pth.SignIn -> (model, Cmd.none)
            _          -> (model, Cmd.none)