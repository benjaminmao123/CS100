#pragma once

#include <string>

class CommandBase
{
public:
    CommandBase() 
    {
        
    }
    
    virtual bool Execute() = 0;
};