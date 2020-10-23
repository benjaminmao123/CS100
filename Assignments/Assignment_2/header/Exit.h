#pragma once

#include <vector>
#include <string>

#include "Command.h"

class Exit : public Command
{
public:
    Exit(const std::vector<std::string>&
        args = std::vector<std::string>());

    virtual bool Execute() override;
};