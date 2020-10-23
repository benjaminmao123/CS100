#include "../header/Parenthesis.h"

LeftParenthesis::LeftParenthesis() :
    Command(Token::TokenType::LEFT_PARENTHESIS, nullptr, nullptr)
{ }

RightParenthesis::RightParenthesis() :
    Command(Token::TokenType::RIGHT_PARENTHESIS, nullptr, nullptr)
{ }