#pragma once

#include "Connector.h"

class InputRedirection : public Connector
{
public:
    InputRedirection(Command* lhs = nullptr,
        Command* rhs = nullptr);
    
    virtual bool Execute() override;
};