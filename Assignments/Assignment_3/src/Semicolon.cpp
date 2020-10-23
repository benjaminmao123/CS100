#include "../header/Semicolon.h"
#include "../header/Command.h"

Semicolon::Semicolon(Command* lhs,
    Command* rhs) :
    Connector(Token::TokenType::SEMICOLON, lhs, rhs)
{ }
    
bool Semicolon::Execute()
{
    Left()->Execute();
    
    return Right()->Execute();
}