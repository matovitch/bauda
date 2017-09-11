module Path exposing (..)

import Route      as Rt exposing ((:=))
import Navigation as Nav

type Path =
    Home          |
    LogIn         |
    SignIn        |
    PasswordReset |
    NotFound

home          = Home          := Rt.static ""
login         = LogIn         := Rt.static "login"
signin        = SignIn        := Rt.static "signin"
passwordReset = PasswordReset := Rt.static "password_reset"
notFound      = NotFound      := Rt.static "not_found"

sitemap =
    Rt.router
        [
            home,
            login,
            signin,
            passwordReset,
            notFound
        ]

fromString : String -> Path
fromString = Rt.match sitemap >> Maybe.withDefault NotFound

toString : Path -> String
toString path =
    case path of
        Home          -> Rt.reverse home          []
        LogIn         -> Rt.reverse login         []
        SignIn        -> Rt.reverse signin        []
        PasswordReset -> Rt.reverse passwordReset []
        _             -> Rt.reverse notFound      []

fromLocation : Nav.Location -> Path
fromLocation = .pathname >> fromString

goto : Path -> Cmd msg
goto = toString >> Nav.newUrl

back : Int -> Cmd msg
back steps = Nav.back steps