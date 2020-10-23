#include "../header/Connector.h"

Connector::Connector(Token::TokenType type,
    Command* lhs,
    Command* rhs) :
    Command(type, lhs, rhs)
{ }

Connector::~Connector()
{ }


