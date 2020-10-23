#include "../header/Token.h"
#include "../header/Command.h"
#include "../header/Exit.h"
#include "../header/Test.h"
#include "../header/Semicolon.h"
#include "../header/And.h"
#include "../header/Or.h"
#include "../header/Parenthesis.h"

std::unordered_map<Token::TokenType, std::string> Token::typeToStringMap =
{
    { Token::TokenType::NONE, "none" },
    { Token::TokenType::COMMAND, "command" },
    { Token::TokenType::CONNECTOR, "connector" },
    { Token::TokenType::EXIT, "exit" },
    { Token::TokenType::TEST, "test" },
    { Token::TokenType::SEMICOLON, ";" },
    { Token::TokenType::AND, "&&"},
    { Token::TokenType::OR, "||"},
    { Token::TokenType::LEFT_PARENTHESIS, "("},
    { Token::TokenType::RIGHT_PARENTHESIS, ")"},
    { Token::TokenType::LEFT_LEGACY_TEST, "["},
    { Token::TokenType::RIGHT_LEGACY_TEST, "]"}
};

std::unordered_map<std::string, Token::TokenType> Token::stringToTypeMap =
{
    { "exit", Token::TokenType::EXIT },
    { "test", Token::TokenType::TEST },
    { ";", Token::TokenType::SEMICOLON },
    { "&&", Token::TokenType::AND },
    { "||", Token::TokenType::OR },
    { "(", Token::TokenType::LEFT_PARENTHESIS },
    { ")", Token::TokenType::RIGHT_PARENTHESIS },
    { "[", Token::TokenType::LEFT_LEGACY_TEST },
    { "]", Token::TokenType::RIGHT_LEGACY_TEST }
};

Token::Token(TokenType type,
    Command* lhs,
    Command* rhs) :
    type(type),
    lhs(lhs),
    rhs(rhs)
{ }

Token::~Token()
{ }

bool Token::Execute()
{ 
    return true;
}

const Command* Token::Left() const
{
    return lhs;
}

const Command* Token::Right() const
{
    return rhs;
}

Command* Token::Left()
{
    return lhs;
}

Command* Token::Right()
{
    return rhs;
}

void Token::Left(Command* cmd)
{
    lhs = cmd;
}

void Token::Right(Command* cmd)
{
    rhs = cmd;
}

const std::string& Token::TypeToString() const
{
    return typeToStringMap.at(type);
}

Token::TokenType Token::Type() const
{
    return type;
}

Command* Token::Create(TokenType type)
{
    switch (type)
    {
    case TokenType::COMMAND:
        return new Command();
    case TokenType::EXIT:
        return new Exit();
    case TokenType::TEST:
        return new Test();
    case TokenType::SEMICOLON:
        return new Semicolon();
    case TokenType::AND:
        return new And();
    case TokenType::OR:
        return new Or();
    case TokenType::LEFT_PARENTHESIS:
        return new LeftParenthesis();
    case TokenType::RIGHT_PARENTHESIS:
        return new RightParenthesis();
    case TokenType::LEFT_LEGACY_TEST:
        return new LeftLegacyTest();
    case TokenType::RIGHT_LEGACY_TEST:
        return new RightLegacyTest();
    default:
        break;
    }
    
    return nullptr;
}

std::string Token::GetString(TokenType type)
{
    if (typeToStringMap.find(type) == typeToStringMap.end())
        return "";

    return typeToStringMap.at(type);
}

Token::TokenType Token::GetEnum(const std::string& tokenStr)
{
    if (stringToTypeMap.find(tokenStr) == stringToTypeMap.end())
        return TokenType::NONE;

    return stringToTypeMap.at(tokenStr);
}