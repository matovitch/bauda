module Server exposing (..)

import Message   as Msg exposing (Message)
import WebSocket as WSk
import Model     as Mdl
import Config    as Cfg

listen : Mdl.Model -> Sub Message
listen =
    \m -> WSk.listen Cfg.server Msg.ServerReply

send : String -> Cmd Message
send = 
    WSk.send Cfg.server