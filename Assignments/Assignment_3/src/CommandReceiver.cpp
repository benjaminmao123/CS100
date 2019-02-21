#include "CommandReceiver.h"

void CommandReceiver::Terminate() const
{
	exit(EXIT_SUCCESS);
}

bool CommandReceiver::RunProgram(std::vector<std::string> &ArgumentList) const
{
	if (ArgumentList[0] == "exit")
	{
		Terminate();
	}
	else if (ArgumentList[0] == "cd" || ArgumentList[0] == "..")
	{
		if (!ChangeDirectory(ArgumentList))
    	{
    		return false;
    	}
    	
    	return true;
	}
	else if (ArgumentList[0] == "help")
	{
		std::cout << "List of built-in commands: \nexit\n" << "cd\n" << "test\n";
		return true;
	}
	else if (ArgumentList[0] == "test" || ArgumentList[0] == "[")
	{
		if (!Test(ArgumentList))
		{
			return false;
		}
		
		return true;
	}
	
	std::vector<char *> Args;
	
	for (auto i = 0U; i < ArgumentList.size(); ++i)
	{
		Args.emplace_back(const_cast<char *>(ArgumentList[i].c_str()));
	}
	
	Args.emplace_back(nullptr);
    
    pid_t pid = fork();
	
	if (pid > 0)
	{
        int Status;
        
        if (waitpid(pid, &Status, 0) == -1) 
        {       
            perror("wait");
        }
        
        if (WEXITSTATUS(Status) != 0) 
        {
            return false;
        }
	}
	else if (pid == 0)
	{
		if (execvp(Args[0], Args.data()) == -1)
		{
			std::cout << "Shell: " << Args[0] << ": " << "command not found" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror("fork");
		return false;
	}
	
	return true;
}

bool CommandReceiver::ChangeDirectory(std::vector<std::string> &ArgumentList) const
{
	std::string temp;
	
	for (auto i = 1U; (i + 1) < ArgumentList.size(); ++i)
	{
		temp += ArgumentList[i] + " ";
	}
	
	if (ArgumentList.size() != 1)
	{
		temp += ArgumentList[ArgumentList.size() - 1];
	}

	if (temp.empty())
	{
		if (chdir(getenv("HOME")))
		{
			perror("getenv");
			return false;
		}
	}
	else if (temp[0] == '~')
	{
		if (chdir(getenv("HOME")))
		{
			perror("getenv");
			return false;
		}	
	}
	else if (chdir(temp.c_str()))
	{
		std::cout << "Shell: cd: " << temp << ": No such file or directory\n";
		return false; 
	}
	
	return true;
}

bool CommandReceiver::Test(std::vector<std::string> &ArgumentList) const
{
	struct stat buf;
	
	if (ArgumentList[0] == "test")
	{
		if (ArgumentList.size() == 1)
		{
			std::cout << "Shell: syntax error: test: missing path name\n";
			return false;
		}
		else if (ArgumentList.size() == 2 && (ArgumentList[1] == "-e" || ArgumentList[1] == "-f" || ArgumentList[1] == "-d"))
		{
			std::cout << "Shell: syntax error: test: missing path name\n";
			return false;
		}
		else
		{
			if (ArgumentList[1] == "-e")
			{
				std::string path = ArgumentList[2];
			
				if (!stat(path.c_str(), &buf))
				{
					std::cout << "(True)\n";
					return true;
				}
				
				std::cout << "(False)\n";
				return false;
			}
			else if (ArgumentList[1] == "-f")
			{
				std::string path = ArgumentList[2];
				
				if (stat(path.c_str(), &buf))
				{
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
			else if (ArgumentList[1] == "-d")
			{
				std::string path = ArgumentList[2];
				
				if (stat(path.c_str(), &buf))
				{
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
			else
			{
				std::string path = ArgumentList[1];
				
				if (!stat(path.c_str(), &buf))
				{
					std::cout << "(True)\n";
					return true;
				}
				
				std::cout << "(False)\n";
				return false;
			}	
		}
	}
	else
	{
		if (ArgumentList.size() == 2)
		{
			std::cout << "Shell: syntax error: test: missing path name\n";
			return false;
		}
		else if (ArgumentList.size() == 3 && (ArgumentList[1] == "-e" || ArgumentList[1] == "-f" || ArgumentList[1] == "-d"))
		{
			std::cout << "Shell: syntax error: test: missing path name\n";
			return false;			
		}
		if (ArgumentList[1] == "-e")
		{
			std::string path = ArgumentList[2];
		
			if (!stat(path.c_str(), &buf))
			{
				std::cout << "(True)\n";
				return true;
			}
			
			std::cout << "(False)\n";
			return false;
		}
		else if (ArgumentList[1] == "-f")
		{
			std::string path = ArgumentList[2];
			
			if (stat(path.c_str(), &buf))
			{
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
		else if (ArgumentList[1] == "-d")
		{
			std::string path = ArgumentList[2];
			
			if (stat(path.c_str(), &buf))
			{
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
		else
		{
			std::string path = ArgumentList[1];
			
			if (!stat(path.c_str(), &buf))
			{
				std::cout << "(True)\n";
				return true;
			}
			
			std::cout << "(False)\n";
			return false;
		}
	}
	
	return true;
}