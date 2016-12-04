module Bauda exposing (main)

import Json.Decode   as JsD
import Navigation    as Nav
import Message       as Msg
import Update        as Upd 
import Server        as Srv
import Model         as Mdl
import View

main : Program (Maybe JsD.Value) Mdl.Model Msg.Message
main = 
    Nav.programWithFlags Msg.fromPath
    {
        init          = Mdl.init,
        view          = View.view,
        update        = (\msg -> (Upd.update msg) >> Mdl.store),
        subscriptions = Srv.listen
    }