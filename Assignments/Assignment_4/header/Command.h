#pragma once

#include <string>
#include <vector>

#include "Token.h"

class Command : public Token
{
public:
    Command(TokenType type = TokenType::COMMAND,
        const std::vector<std::string>&
        args = std::vector<std::string>(),
        Command* lhs = nullptr,
        Command* rhs = nullptr);
    Command(TokenType type,
        Command* lhs,
        Command* rhs);        

    virtual ~Command();

    virtual bool Execute();

    void SetArgs(const std::vector<std::string>& args);
    const std::vector<std::string>& GetArgs() const;
    
    int In() const;
    void In(int value);
    int Out() const;
    void Out(int value);

private:
    std::vector<std::string> args;
    
    int fdin;
    int fdout;
};