#pragma once

#include <vector>
#include <sstream>
#include <initializer_list>
#include <string>

class Command;

namespace ParserLibrary
{
	enum class ShuntingState
	{
		EXPECT_COMMAND,
		EXPECT_CONNECTOR
	};

    std::vector<std::string> Tokenize(const std::string& input);
    std::vector<Command*> Tokenize(const std::vector<std::string>& input);
    std::string ParseComment(const std::string& input, 
        const std::string& comment);
    std::vector<Command*> GeneratePostfix(std::vector<Command*>& infix);
}