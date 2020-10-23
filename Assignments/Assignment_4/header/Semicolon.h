#pragma once

#include "Connector.h"

class Semicolon : public Connector
{
public:
    Semicolon(Command* lhs = nullptr,
        Command* rhs = nullptr);
        
    virtual bool Execute() override;
};