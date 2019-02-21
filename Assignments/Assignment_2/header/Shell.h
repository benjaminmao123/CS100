#pragma once

#include "ConcreteSingleCommand.h"
#include "ConcreteConnector.h"
#include "CommandInvoker.h"
#include "Parser.h"

#include <cstring>

class Shell
{
public:
    Shell();
    void Run();
    void PrintPrompt(bool &InfoAvailable);
    bool ExecuteCommands();
    void BuildTree();
    void CreateCommands();
    
private:
    std::shared_ptr<CommandReceiver> Receiver;
    std::shared_ptr<CommandInvoker> Invoker;
    std::shared_ptr<ConcreteSingleCommand> Command;
    std::shared_ptr<ConcreteConnector> Connector;
    std::queue<std::shared_ptr<CommandBase>> SingleCommandList;
    std::queue<std::string> ConnectorList;
    std::deque<std::shared_ptr<CommandBase>> CommandTree;
    std::vector<std::string> InputVec;
};