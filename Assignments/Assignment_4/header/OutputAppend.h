#pragma once

#include "Connector.h"

class OutputAppend : public Connector
{
public:
    OutputAppend(Command* lhs = nullptr,
        Command* rhs = nullptr);
    
    virtual bool Execute() override;
};