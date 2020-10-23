#pragma once

#include <string>

#include "Command.h"
#include "Token.h"

class Connector : public Command
{
public:
    Connector(TokenType type = TokenType::CONNECTOR,
        Command* lhs = nullptr,
        Command* rhs = nullptr);
    
    virtual ~Connector() = 0;
};