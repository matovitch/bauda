module Path exposing (..)

import Route      as Rt exposing ((:=))
import Navigation as Nav

type Path =
    Home           |
    LogIn          |
    SignIn         |
    ForgotPassword |
    NotFound

home           = Home           := Rt.static ""
login          = LogIn          := Rt.static "login"
signin         = SignIn         := Rt.static "signin"
forgotPassword = ForgotPassword := Rt.static "forgot_password"
notFound       = NotFound       := Rt.static "not_found"

sitemap =
    Rt.router
        [
            home,
            login,
            signin,
            forgotPassword,
            notFound
        ]

fromString : String -> Path
fromString = Rt.match sitemap >> Maybe.withDefault NotFound

toString : Path -> String
toString path =
    case path of
        Home           -> Rt.reverse home           []
        LogIn          -> Rt.reverse login          []
        SignIn         -> Rt.reverse signin         []
        ForgotPassword -> Rt.reverse forgotPassword []
        _              -> Rt.reverse notFound       []

fromLocation : Nav.Location -> Path
fromLocation = .pathname >> fromString

goto : Path -> Cmd msg
goto = toString >> Nav.newUrl

back : Int -> Cmd msg
back steps = Nav.back steps