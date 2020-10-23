#include <iostream>

#include "../header/Parser.h"
#include "../header/ParserLibrary.h"
#include "../header/Command.h"

std::vector<Command*> Parser::operator()(const std::string& command) const
{
    std::string result = ParserLibrary::ParseComment(command, "#");
    std::vector<std::string> strTokens = ParserLibrary::Tokenize(result);
    std::vector<Command*> tokens = ParserLibrary::Tokenize(strTokens);
    std::vector<Command*> postfix = ParserLibrary::GeneratePostfix(tokens);

    return postfix;
}