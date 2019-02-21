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
        return Receiver->RunProgram(ArgumentList);
    }
    
    void Push(std::string &Argument)
    {
		ArgumentList.emplace_back(Argument);
    }
    
    std::string GetCommand(const int i) const
    {
        return ArgumentList[i];
    }
    
private:
    std::shared_ptr<CommandReceiver> Receiver;
    std::vector<std::string> ArgumentList;
};