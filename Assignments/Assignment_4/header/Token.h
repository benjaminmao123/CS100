#pragma once

#include <string>
#include <unordered_map>

class Command;

class Token
{
public:
    enum class TokenType
    {
        NONE,
        COMMAND,
        CONNECTOR,
        EXIT,
        TEST,
        SEMICOLON,
        AND,
        OR,
        LEFT_PARENTHESIS,
        RIGHT_PARENTHESIS,
        LEFT_LEGACY_TEST,
        RIGHT_LEGACY_TEST,
        REDIRECTION,
        PIPE,
        INPUT_REDIRECTION,
        OUTPUT_REDIRECTION,
        OUTPUT_APPEND,
        CHANGE_DIRECTORY
    };

    Token(TokenType type = TokenType::NONE,
        Command* lhs = nullptr,
        Command* rhs = nullptr);

    virtual ~Token() = 0;

    virtual bool Execute();

    const Command* Left() const;
    const Command* Right() const;
    Command* Left();
    Command* Right();
    
    void Left(Command* cmd);
    void Right(Command* cmd);

    const std::string& TypeToString() const;
    TokenType Type() const;

    static Command* Create(TokenType type);

    static std::string GetString(TokenType type);
    static TokenType GetEnum(const std::string& tokenStr);    

private:
    TokenType type;
    Command* lhs;
    Command* rhs;
    
    static std::unordered_map<TokenType, std::string> typeToStringMap;
    static std::unordered_map<std::string, TokenType> stringToTypeMap;    
};