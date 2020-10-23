#include <cstdlib>

#include "../header/Exit.h"

Exit::Exit(const std::vector<std::string>& args) :
    Command(Token::TokenType::EXIT, args)
{ }

bool Exit::Execute()
{
    exit(EXIT_SUCCESS);
}