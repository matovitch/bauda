module Server exposing (send, listen)

import Message as Msg exposing (Message)
import Model   as Mdl exposing (Model  )
import Config  as Cfg

import WebSocket as WSk

listen : Model -> Sub Message
listen model =
    WSk.listen Cfg.server Msg.ServerReply

send : String -> Cmd Message
send = 
    WSk.send Cfg.server