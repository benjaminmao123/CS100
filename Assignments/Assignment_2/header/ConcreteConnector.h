#pragma once

#include "CommandBase.h"

#include <memory>

class ConcreteConnector : public CommandBase
{
public:
    ConcreteConnector()
    {
        
    }
    
    virtual bool Execute() = 0;
    virtual std::string GetCommand(const int i) const = 0;
};

class Semicolon : public ConcreteConnector
{
public:
    Semicolon(std::shared_ptr<CommandBase> lhs, std::shared_ptr<CommandBase> rhs) : lhs(lhs), rhs(rhs)
    {

    }
    
    bool Execute() 
    {
        lhs->Execute();
        return rhs->Execute();
    }

    std::string GetCommand(const int i) const
    {
        if (!i)
        {
            return lhs->GetCommand(0);
        }
        
        return rhs->GetCommand(0);
    }
    
private:
    std::shared_ptr<CommandBase> lhs;
    std::shared_ptr<CommandBase> rhs;
};

class And : public ConcreteConnector
{
public:
    And(std::shared_ptr<CommandBase> lhs, std::shared_ptr<CommandBase> rhs) : lhs(lhs), rhs(rhs)
    {

    }

    bool Execute() 
    {
        if (!lhs->Execute())
        {
            return false;
        }
        
        return rhs->Execute();
    }
    
    std::string GetCommand(const int i) const
    {
        if (!i)
        {
            return lhs->GetCommand(0);
        }
        
        return rhs->GetCommand(0);
    }

private:
    std::shared_ptr<CommandBase> lhs;
    std::shared_ptr<CommandBase> rhs;
};

class Or : public ConcreteConnector
{
public:
    Or(std::shared_ptr<CommandBase> lhs, std::shared_ptr<CommandBase> rhs) : lhs(lhs), rhs(rhs)
    {

    }
    
    bool Execute()
    {
        if (!lhs->Execute())
        {
            return rhs->Execute();
        }
        
        return true;
    }
    
    std::string GetCommand(const int i) const
    {
        if (!i)
        {
            return lhs->GetCommand(0);
        }
        
        return rhs->GetCommand(0);
    }

private:
    std::shared_ptr<CommandBase> lhs;
    std::shared_ptr<CommandBase> rhs;
};