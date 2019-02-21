#pragma once

#include "CommandBase.h"

#include <memory>

class CommandInvoker
{
public:
    void SetCommand(std::shared_ptr<CommandBase> Command)
    {
        this->Command = Command;
    }
    
    bool RunCommand() const
    {
        return Command->Execute();
    }
    
private:
    std::shared_ptr<CommandBase> Command;
};