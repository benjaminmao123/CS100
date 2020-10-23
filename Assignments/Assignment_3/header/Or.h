#pragma once

#include "Connector.h"

class Or : public Connector
{
public:
    Or(Command* lhs = nullptr,
        Command* rhs = nullptr);
        
    virtual bool Execute() override;
};