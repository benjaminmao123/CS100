#pragma once

#include <vector>
#include <string>
#include <unordered_set>

#include "Command.h"

class ChangeDirectory : public Command
{
public:
    ChangeDirectory(const std::vector<std::string>&
        args = std::vector<std::string>());

    virtual bool Execute() override;
};