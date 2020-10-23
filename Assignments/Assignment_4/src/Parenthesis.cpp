#include "../header/Parenthesis.h"

LeftParenthesis::LeftParenthesis() :
    Command(Token::TokenType::LEFT_PARENTHESIS)
{ }

RightParenthesis::RightParenthesis() :
    Command(Token::TokenType::RIGHT_PARENTHESIS)
{ }
