module Subscriptions exposing (subscriptions)

import WebSocket as WSk
import Message   as Msg
import Model     as Mdl
import Config    as Cfg

subscriptions : Mdl.Model -> Sub Msg.Message
subscriptions model =
    WSk.listen Cfg.server Msg.ServerReply