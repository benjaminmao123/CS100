#pragma once

#include <vector>
#include <string>
#include <unordered_set>

#include "Command.h"

class Test : public Command
{
public:
    Test(const std::vector<std::string>&
        args = std::vector<std::string>());

    virtual bool Execute() override;

private:
    static std::vector<std::string> validFlags;
};

class LeftLegacyTest : public Command
{
public:
    LeftLegacyTest();
};

class RightLegacyTest : public Command
{
public:
    RightLegacyTest();
};