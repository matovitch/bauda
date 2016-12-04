module Message exposing (..)

import Query      as Qry exposing (Query)
import Path       as Pth exposing (Path)
import Navigation as Nav

type Message = 
    GotoPath        Path   |
    ChangePath      Path   |
    Username        String |
    Password        String |
    Password2       String |
    Email           String |
    ServerQuery     Query  |
    ServerReply     String |
    Nothing

fromPath : Nav.Location -> Message
fromPath location =
    ChangePath (Pth.fromLocation location)