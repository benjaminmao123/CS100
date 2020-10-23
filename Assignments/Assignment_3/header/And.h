#pragma once

#include "Connector.h"

class And : public Connector
{
public:
    And(Command* lhs = nullptr,
        Command* rhs = nullptr);
        
    virtual bool Execute() override;
};