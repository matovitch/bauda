module Bauda exposing (..)

import Subscriptions as Sub
import Json.Decode   as JsD
import Navigation    as Nav
import Update        as Upd 
import Model         as Mdl
import Path          as Pth
import View          as See

main : Program (Maybe JsD.Value)
main = 
    Nav.programWithFlags (Nav.makeParser Pth.fromLocation)
    {
        init          = Mdl.init,
        view          = See.view,
        update        = (\msg -> (Upd.update    msg) >> Mdl.store),
        urlUpdate     = (\msg -> (Upd.urlUpdate msg) >> Mdl.store),
        subscriptions = Sub.subscriptions
    }