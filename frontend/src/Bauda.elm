module Bauda exposing (..)

import Message       as Msg exposing (Message)
import Update        as Upd exposing (update )
import Model         as Mdl exposing (Model  )
import View          as Vw  exposing (view   )
import Server        as Srv

import Json.Decode   as JsD
import Navigation    as Nav

main : Program (Maybe JsD.Value) Model Message
main = 
    Nav.programWithFlags Msg.fromPath
    {
        init          = Mdl.init,
        view          = view,
        update        = (\msg -> (update msg) >> Mdl.store),
        subscriptions = Srv.listen
    }