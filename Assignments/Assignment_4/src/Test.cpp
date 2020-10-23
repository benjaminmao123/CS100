#include <sys/stat.h>
#include <iostream>
#include <algorithm>

#include "../header/Test.h"

std::vector<std::string> Test::validFlags =
{
	"-e",
	"-d",
	"-f"
};

Test::Test(const std::vector<std::string>& args) :
    Command(Token::TokenType::TEST, args)
{ }

bool Test::Execute()
{
	struct stat buf;
	
	if (GetArgs().size() > 1)
	{
		auto flagPos = GetArgs().begin();
		
		for (const auto& flag : validFlags)
		{
			flagPos = std::find(GetArgs().begin(), GetArgs().end(), flag);
			
			if (flagPos != GetArgs().end())
				break;
		}
		
		std::string path = *(flagPos + 1);
			
		if (*flagPos == "-e")
		{
			if (!stat(path.c_str(), &buf))
			{
				std::cout << "(True)\n";
				
				return true;
			}
			
			std::cout << "(False)\n";
			
			return false;
		}
		else if (*flagPos == "-f")
		{
			if (stat(path.c_str(), &buf))
			{
				std::cout << "(False)\n";
				
				return false;
			}
			
			if (S_ISREG(buf.st_mode))
			{
				std::cout << "(True)\n";
				
				return true;
			}
			
			std::cout << "(False)\n";
			
			return false;
		}
		else if (*flagPos == "-d")
		{
			if (stat(path.c_str(), &buf))
			{
				std::cout << "(False)\n";
				
				return false;
			}
			
			if (S_ISDIR(buf.st_mode))
			{
				std::cout << "(True)\n";
				
				return true;
			}
			
			std::cout << "(False)\n";
			
			return false;
		}
	}
	
	return false;
}

LeftLegacyTest::LeftLegacyTest() :
    Command(Token::TokenType::LEFT_LEGACY_TEST)
{ }

RightLegacyTest::RightLegacyTest() :
    Command(Token::TokenType::RIGHT_LEGACY_TEST)
{ }