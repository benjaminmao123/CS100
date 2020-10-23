#include "../header/And.h"
#include "../header/Command.h"

And::And(Command* lhs,
    Command* rhs) :
    Connector(Token::TokenType::AND, lhs, rhs)
{ }
    
bool And::Execute()
{
    if (Left()->Execute())
        return Right()->Execute();
        
    return false;
}