#pragma once

#include "CommandBase.h"
#include "CommandReceiver.h"

#include <memory>

class ConcreteSingleCommand : public CommandBase
{
public:
    ConcreteSingleCommand(std::shared_ptr<CommandReceiver> Receiver) : Receiver(Receiver)
    {

    }
    
    bool Execute()
    {
        return Receiver->RunProgram(ArgumentList, fdin, fdout);
    }
    
private:
    std::shared_ptr<CommandReceiver> Receiver;
};