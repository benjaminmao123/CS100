#include <iostream>
#include <fcntl.h>

#include "../header/InputRedirection.h"
#include "../header/Token.h"

InputRedirection::InputRedirection(Command* lhs,
    Command* rhs) :
    Connector(Token::TokenType::INPUT_REDIRECTION, lhs, rhs)
{ }

bool InputRedirection::Execute()
{
    std::string file = Right()->GetArgs().front();
    
    int fdin = open(file.c_str(), O_RDONLY);
    
    if (fdin == -1)
    {
        std::cout << "Shell: error: file `" << file << "' does not exist\n";
        
        return false;
    }
    
    Left()->In(fdin);
    Right()->Out(Out());
    
    return Left()->Execute();
}