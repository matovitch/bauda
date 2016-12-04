module Bauda exposing (..)

import Subscriptions as Sub
import Json.Decode   as JsD
import Navigation    as Nav
import Message       as Msg
import Update        as Upd 
import Model         as Mdl
import Path          as Pth
import View

main : Program (Maybe JsD.Value) Mdl.Model Msg.Message
main = 
    Nav.programWithFlags Msg.fromPath
    {
        init          = Mdl.init,
        view          = View.view,
        update        = (\msg -> (Upd.update msg) >> Mdl.store),
        subscriptions = Sub.subscriptions
    }