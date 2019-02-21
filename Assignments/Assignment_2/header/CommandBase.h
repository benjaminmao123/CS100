#pragma once

#include <string>

class CommandBase
{
public:
    CommandBase() 
    {
        
    }
    
    virtual bool Execute() = 0;
    
    virtual std::string GetCommand(const int i) const = 0;
};