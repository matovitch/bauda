module Query exposing (..)

type Query = 
    LogIn  |
    SignIn


toString : Query -> String
toString query =
    case query of
        LogIn  -> "login"
        SignIn -> "signin"