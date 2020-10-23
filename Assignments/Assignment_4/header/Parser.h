#pragma once

#include <string>
#include <vector>

class Command;

class Parser
{
public:
    Parser(const std::string& regex);

    std::vector<Command*> operator()(const std::string& command) const;
    
private:
    std::string regex;
};