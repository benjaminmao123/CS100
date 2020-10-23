#pragma once

#include <string>
#include <vector>

#include "Parser.h"
#include "Executor.h"

class Command;

class Shell
{
public:
    void Run();

private:
    void PrintCommandPrompt() const;
    void GetCommand();
    void ParseCommand();
    void ExecuteCommand();
    void Clear();
    
    std::string command;
    std::vector<Command*> postfix;
    Parser parser;
    Executor executor;
};