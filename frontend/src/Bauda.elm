import Subscriptions as Sub
import Json.Decode   as JsD
import Update        as Upd 
import Model         as Mdl
import Html.App
import View

main : Program (Maybe JsD.Value)
main = 
    Html.App.programWithFlags
    {
        init          = Mdl.init,
        view          = View.view,
        update        = Upd.update,
        subscriptions = Sub.subscriptions
    }