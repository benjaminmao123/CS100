#pragma once

#include <string>
#include <unistd.h>
#include <vector>
#include <memory>
#include <iostream>

class CommandBase
{
public:
    CommandBase() : fdin(STDIN_FILENO), fdout(STDOUT_FILENO), Type("")
    {
        
    }
    
    CommandBase(std::string Type) : fdin(STDIN_FILENO), fdout(STDOUT_FILENO), Type(Type)
    {
        
    }    
    
    virtual bool Execute() = 0;
    
    void Push(std::string &Argument)
    {
		ArgumentList.emplace_back(Argument);
    }
    
    const std::string GetArgument(const int index) const
    {
        if (index < 0)
        {
            return ArgumentList[0];
        }
        
        if (index >= static_cast<int>(ArgumentList.size()))
        {
            return ArgumentList[ArgumentList.size() - 1];
        }
        
        return ArgumentList[index];
    }
    
    int fdin;
    int fdout;
    std::string Type;
    
protected:
    std::vector<std::string> ArgumentList;
};