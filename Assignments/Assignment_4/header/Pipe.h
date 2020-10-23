#pragma once

#include "Connector.h"

class Pipe : public Connector
{
public:
    Pipe(Command* lhs = nullptr,
        Command* rhs = nullptr);
    
    virtual bool Execute() override;
};