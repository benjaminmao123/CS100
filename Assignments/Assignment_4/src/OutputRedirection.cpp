#include <iostream>
#include <fcntl.h>

#include "../header/OutputRedirection.h"
#include "../header/Command.h"

OutputRedirection::OutputRedirection(Command* lhs,
    Command* rhs) :
    Connector(Token::TokenType::OUTPUT_REDIRECTION, lhs, rhs)
{ }

bool OutputRedirection::Execute()
{
    std::string file = Right()->GetArgs().front();
    
    int fdout = open(file.c_str(), O_WRONLY | 
        O_CREAT | O_TRUNC, S_IRUSR | 
        S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    
    if (fdout == -1)
    {
        std::cout << "Shell: error: file `" << file << "' does not exist\n";
        
        return false;            
    }
    
    Left()->In(In());
    Left()->Out(fdout);
    
    return Left()->Execute();
}