#pragma once

#include <string>
#include <vector>

class Command;

class Parser
{
public:
    std::vector<Command*> operator()(const std::string& command) const;
};