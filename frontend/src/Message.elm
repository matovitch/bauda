module Message exposing (..)

type Message = 
    GotoLogIn              |
    GotoSignIn             |
    Username        String |
    Password        String |
    Password2       String |
    Email           String |
    RunLogIn               |
    RunSignIn              |
    WebsocketReply  String |
    Nothing
    