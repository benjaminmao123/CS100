#pragma once

#include "ConcreteSingleCommand.h"
#include "ConcreteConnector.h"
#include "CommandInvoker.h"
#include "Parser.h"
#include "ConcreteRedirection.h"

#include <cstring>
#include <queue>

class Shell
{
public:
    Shell();
    void Run();
    void PrintPrompt(bool &InfoAvailable);
    bool ExecuteCommands();
    std::shared_ptr<CommandBase> BuildTree(std::vector<std::shared_ptr<Connectors>> &ConnectorList);
    void CreateCommands();
    
private:
    std::shared_ptr<CommandReceiver> Receiver;
    std::shared_ptr<CommandInvoker> Invoker;
    std::shared_ptr<CommandBase> Command;
    std::shared_ptr<ConcreteConnector> Connector;
    std::queue<std::shared_ptr<CommandBase>> SingleCommandList;
    std::vector<std::shared_ptr<Connectors>> ConnectorList;
    std::vector<std::shared_ptr<CommandBase>> CommandTree;
    std::vector<std::string> InputVec;
};
