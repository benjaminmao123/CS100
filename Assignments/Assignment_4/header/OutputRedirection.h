#pragma once

#include "Connector.h"

class OutputRedirection : public Connector
{
public:
    OutputRedirection(Command* lhs = nullptr,
        Command* rhs = nullptr);
    
    virtual bool Execute() override;
};