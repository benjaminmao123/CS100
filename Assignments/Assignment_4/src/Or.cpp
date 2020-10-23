#include "../header/Or.h"
#include "../header/Command.h"

Or::Or(Command* lhs,
    Command* rhs) :
    Connector(Token::TokenType::OR, lhs, rhs)
{ }
    
bool Or::Execute()
{
    if (!Left()->Execute())
        return Right()->Execute();
        
    return false;
}