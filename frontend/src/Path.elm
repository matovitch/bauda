module Path exposing (..)

import Navigation as Nav
import Route      as Rt exposing ((:=))

type Path =
    Home   |
    LogIn  |
    SignIn |
    NotFound

home     = Home     := Rt.static ""
login    = LogIn    := Rt.static "login"
signin   = SignIn   := Rt.static "signin"
notFound = NotFound := Rt.static "not_found"

sitemap =
    Rt.router
        [
            home,
            login,
            signin,
            notFound
        ]

fromString : String -> Path
fromString = Rt.match sitemap >> Maybe.withDefault NotFound

toString : Path -> String
toString path =
    case path of
        Home   -> Rt.reverse home     []
        LogIn  -> Rt.reverse login    []
        SignIn -> Rt.reverse signin   []
        _      -> Rt.reverse notFound []

fromLocation : Nav.Location -> Path
fromLocation = .pathname >> fromString

navigateTo : Path -> Cmd msg
navigateTo = toString >> Nav.newUrl