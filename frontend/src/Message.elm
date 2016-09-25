module Message exposing (..)

import Path exposing (Path)

type Message = 
    ToPath          Path   |
    Username        String |
    Password        String |
    Password2       String |
    Email           String |
    RunLogIn               |
    RunSignIn              |
    WebsocketReply  String |
    Nothing