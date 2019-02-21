#pragma once

#include "CommandBase.h"

#include <memory>

class ConcreteConnector : public CommandBase
{
public:
    ConcreteConnector(std::shared_ptr<CommandBase> lhs, std::shared_ptr<CommandBase> rhs) : lhs(lhs), rhs(rhs)
    {
        
    }
    
    virtual bool Execute() = 0;
    
protected:
    std::shared_ptr<CommandBase> lhs;
    std::shared_ptr<CommandBase> rhs;
};

class Semicolon : public ConcreteConnector
{
public:
    Semicolon(std::shared_ptr<CommandBase> lhs, std::shared_ptr<CommandBase> rhs) : ConcreteConnector(lhs, rhs)
    {

    }
    
    bool Execute() 
    {
        lhs->Execute();
        
        rhs->fdin = this->fdin;
        rhs->fdout = this->fdout;
        
        return rhs->Execute();
    }
};

class And : public ConcreteConnector
{
public:
    And(std::shared_ptr<CommandBase> lhs, std::shared_ptr<CommandBase> rhs) : ConcreteConnector(lhs, rhs)
    {

    }

    bool Execute() 
    {
        if (!lhs->Execute())
        {
            return false;
        }
        
        rhs->fdin = this->fdin;
        rhs->fdout = this->fdout;
        
        return rhs->Execute();
    }
};

class Or : public ConcreteConnector
{
public:
    Or(std::shared_ptr<CommandBase> lhs, std::shared_ptr<CommandBase> rhs) : ConcreteConnector(lhs, rhs)
    {

    }
    
    bool Execute()
    {
        lhs->fdout = this->fdout;
        
        if (!lhs->Execute())
        {
            rhs->fdin = this->fdin;
            rhs->fdout = this->fdout;
            return rhs->Execute();
        }
        
        return true;
    }
};