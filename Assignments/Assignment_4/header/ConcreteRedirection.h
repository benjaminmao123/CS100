#include "CommandBase.h"

#include <memory>
#include <sys/stat.h> 
#include <fcntl.h>

class ConcreteRedirection : public CommandBase
{
public:
    ConcreteRedirection(std::shared_ptr<CommandBase> lhs, std::shared_ptr<CommandBase> rhs, std::string Type) : CommandBase(Type), lhs(lhs), rhs(rhs)
    {
        
    }
    
    virtual bool Execute() = 0;
    
protected:
    std::shared_ptr<CommandBase> lhs;
    std::shared_ptr<CommandBase> rhs;
};

class Pipe : public ConcreteRedirection
{
public:
    Pipe(std::shared_ptr<CommandBase> lhs, std::shared_ptr<CommandBase> rhs, std::string Type) : ConcreteRedirection(lhs, rhs, Type)
    {

    }
    
    bool Execute()
    {
        if (this->fdout != 1)
        {
            int fds[2];
        
            if (pipe(fds) == -1)
            {
                perror("pipe");
                return false;
            }
               
            lhs->fdout = fds[1];
            if (!lhs->Execute())
            {
                return false;
            }
            
            close(fds[1]);
            
            rhs->fdin = fds[0];
            rhs->fdout = this->fdout;
            if (!rhs->Execute())
            {
                return false;
            }
            
            close(fds[0]);    
            
            return true;
        }
        
        if (lhs->Type == "<")
        {
            int fds[2];
        
            if (pipe(fds) == -1)
            {
                perror("pipe");
                return false;
            }            
            
            lhs->fdout = fds[1];
            if (!lhs->Execute())
            {
                return false;
            }
            
            close(fds[1]);
            
            rhs->fdin = fds[0];
            if (!rhs->Execute())
            {
                return false;
            }
            
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
               
            lhs->fdout = fds[1];
            if (!lhs->Execute())
            {
                return false;
            }
            
            close(fds[1]);
            
            rhs->fdin = fds[0];
            if (!rhs->Execute())
            {
                return false;
            }
            
            close(fds[0]);
        }
        
        return true;
    }
};

class InputRedirection : public ConcreteRedirection
{
public:
    InputRedirection(std::shared_ptr<CommandBase> lhs, std::shared_ptr<CommandBase> rhs, std::string Type) : ConcreteRedirection(lhs, rhs, Type)
    {
        
    }
    
    bool Execute()
    {
        std::string file = rhs->GetArgument(0);
        
        int fdin = open(file.c_str(), O_RDONLY);
        
        if (fdin == -1)
        {
            std::cout << "Shell: error: file `" << file << "' does not exist\n";
            return false;
        }
        
        lhs->fdin = fdin;
        lhs->fdout = this->fdout;
        
        return lhs->Execute();
    }
};

class OutputRedirection : public ConcreteRedirection
{
public:
    OutputRedirection(std::shared_ptr<CommandBase> lhs, std::shared_ptr<CommandBase> rhs, std::string Type) : ConcreteRedirection(lhs, rhs, Type)
    {
        
    }
    
    bool Execute()
    {
        std::string file = rhs->GetArgument(0);
        
        int fdout = open(file.c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
        
        if (fdout == -1)
        {
            std::cout << "Shell: error: file `" << file << "' does not exist\n";
            return false;            
        }
        
        lhs->fdin = this->fdin;
        lhs->fdout = fdout;
        
        return lhs->Execute();
    }
};

class OutputAppend : public ConcreteRedirection
{
public:
    OutputAppend(std::shared_ptr<CommandBase> lhs, std::shared_ptr<CommandBase> rhs, std::string Type) : ConcreteRedirection(lhs, rhs, Type)
    {
        
    }
    
    bool Execute()
    {
        std::string file = rhs->GetArgument(0);
        
        int fdout = open(file.c_str(), O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
        
        if (fdout == -1)
        {
            std::cout << "Shell: error: file `" << file << "' does not exist\n";
            return false;            
        }
        
        lhs->fdin = this->fdin;
        lhs->fdout = fdout;
        
        return lhs->Execute();
    }
};