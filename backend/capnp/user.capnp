@0xe5938914a32e6f24;

struct Password
{
    hash @0 :Data;
    salt @1 :UInt64;
}

struct User
{
    name     @0 :Text;
    email    @1 :Text;
    password @2 :Password;
}