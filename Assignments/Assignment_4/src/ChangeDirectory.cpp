#include <unistd.h>
#include <iostream>

#include "../header/ChangeDirectory.h"

ChangeDirectory::ChangeDirectory(const std::vector<std::string>& args) :
    Command(Token::TokenType::CHANGE_DIRECTORY, args)
{ }

bool ChangeDirectory::Execute()
{
	std::string dir;
	
	for (std::size_t i = 1; i < GetArgs().size() - 1; ++i)
		dir += GetArgs()[i] + " ";
	
	dir += GetArgs().back();

	if (dir.empty())
	{
		if (chdir(getenv("HOME")))
		{
			perror("getenv");
			
			return false;
		}
	}
	else if (dir.front() == '~')
	{
		if (chdir(getenv("HOME")))
		{
			perror("getenv");
			
			return false;
		}	
	}
	else if (chdir(dir.c_str()))
	{
		std::cout << "Shell: cd: " << dir << ": No such file or directory\n";
		
		return false; 
	}
	
	return true;    
}