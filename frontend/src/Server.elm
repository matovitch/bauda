module Server exposing (send, listen)

import Message as Msg exposing (Message)
import Model   as Mdl exposing (Model  )
import Config  as Cfg

import Platform.Sub as Sub exposing (Sub)
import WebSocket    as WSk
import Time         as Tm

listen : Model -> Sub Message
listen model =
    if model.is_waiting_server 
    then
        Sub.batch 
            [
                WSk.listen Cfg.server Msg.ServerReply,
                Tm.every (Cfg.timeoutInSeconds * Tm.second) Msg.Timeout
            ]
    else
        Sub.none

send : String -> Cmd Message
send = 
    WSk.send Cfg.server