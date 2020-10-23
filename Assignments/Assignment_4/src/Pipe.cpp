#include <unistd.h>

#include "../header/Pipe.h"
#include "../header/Command.h"

Pipe::Pipe(Command* lhs,
    Command* rhs) :
    Connector(Token::TokenType::PIPE, lhs, rhs)
{ }

bool Pipe::Execute()
{
    if (Out() != 1)
    {
        int fds[2];
    
        if (pipe(fds) == -1)
        {
            perror("pipe");
            
            return false;
        }
           
        Left()->Out(fds[1]);
        
        if (!Left()->Execute())
            return false;
        
        close(fds[1]);
        
        Right()->In(fds[0]);
        Right()->Out(Out());
        
        if (!Right()->Execute())
            return false;
        
        close(fds[0]);    
        
        return true;
    }
    
    if (Left()->Type() == Token::TokenType::INPUT_REDIRECTION)
    {
        int fds[2];
    
        if (pipe(fds) == -1)
        {
            perror("pipe");
            
            return false;
        }            
        
        Left()->Out(fds[1]);
        
        if (!Left()->Execute())
            return false;
        
        close(fds[1]);
        
        Right()->In(fds[0]);
        
        if (!Right()->Execute())
            return false;
        
        close(fds[0]);
    }
    else
    {
        int fds[2];
    
        if (pipe(fds) == -1)
        {
            perror("pipe");
            
            return false;
        }
           
        Left()->Out(fds[1]);
        
        if (!Left()->Execute())
            return false;
        
        close(fds[1]);
        
        Right()->In(fds[0]);
        
        if (!Right()->Execute())
            return false;
        
        close(fds[0]);
    }
    
    return true;
}