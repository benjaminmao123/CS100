#include "Shell.h"

Shell::Shell()
{

}

void Shell::Run()
{
    bool Status = true;
    bool InfoAvailable = true;
    Receiver = std::make_shared<CommandReceiver>();
    Invoker = std::make_shared<CommandInvoker>();
    
    while (Status)
    {
        PrintPrompt(InfoAvailable);
        std::string Input;
        getline(std::cin, Input);
        Parser Parser(Input);
        
		if (Parser.ParseInput(InputVec, ConnectorList))
        {
            Status = ExecuteCommands();
        }
    }
}

void Shell::PrintPrompt(bool &InfoAvailable)
{
    static int count = 0;
    
    if (!count)
    {
        std::cout << "\033[H\033[J";
        std::cout << "Welcome to BJShell (Benjamin and Johnathan Shell)!\n" << "If you want the list of the current built-in commands type 'help'\n";
        ++count;
    }
    
    if (InfoAvailable)
    {
        char *UserName = getlogin();
        
        if (UserName == NULL)
        {
            std::cout << "getlogin() failed\n";
            InfoAvailable = false;
        }
    
        char HostName[256] = "/0";
        gethostname(HostName, 256); 
        
        if (HostName == NULL)
        {
            std::cout << "gethostname() failed\n";
            InfoAvailable = false;
        }
        
        char cwd[256];
        
        if (getcwd(cwd, sizeof(cwd)) == NULL)
        {
            InfoAvailable = false;
        }
        
        if (InfoAvailable)
        {
            std::cout << "[" << UserName << "@" << HostName << " " << strrchr(cwd, '/') + 1 << "]";
        }
    }
    
    std::cout << "$ ";
}

void Shell::CreateCommands()
{
	Command = std::make_shared<ConcreteSingleCommand>(Receiver);
	bool HasNext = true;
	std::string Input;

	for (auto i = 0U; i < InputVec.size(); ++i)
	{
		Parser parse;
		bool HasConnector = parse.ParseQuotations(Input, InputVec[i]);
		
		if ((Input == ";" || Input == "&&" || Input == "||" || Input == "|" || Input == "<" || Input == ">" || Input == ">>") && !HasConnector)
		{
	        SingleCommandList.emplace(Command); 
	        
	        if ((i + 1) < InputVec.size())
			{
				Command = std::make_shared<ConcreteSingleCommand>(Receiver);
			}
			else
			{
			    HasNext = false;
			}
		}
		else
		{
            Command->Push(Input);
		}
	}
    
    if (HasNext)
    {
        SingleCommandList.emplace(Command);   
    }
}

bool Shell::ExecuteCommands()
{
    CreateCommands();
    
    if (SingleCommandList.size() >= 2)
    {
		CommandTree.emplace_back(BuildTree(ConnectorList));

		while (!CommandTree.empty())
		{
			Invoker->SetCommand(CommandTree.back());
			Invoker->RunCommand();
			CommandTree.pop_back();
		}
    }
    else
    {
        while (!SingleCommandList.empty())
        {
            Invoker->SetCommand(SingleCommandList.front());
            Invoker->RunCommand();
            SingleCommandList.pop();
        }
    }
    
    return true;
}

std::shared_ptr<CommandBase> Shell::BuildTree(std::vector<std::shared_ptr<Connectors>> &ConnectorList)
{
	std::shared_ptr<CommandBase> lhs;
	std::shared_ptr<CommandBase> rhs;
	std::shared_ptr<CommandBase> Connector;

	for (auto i = 0U; i < ConnectorList.size(); ++i)
	{
		if (ConnectorList[i]->Type == ";")
		{
			if (CommandTree.empty())
			{
				if (ConnectorList[i]->SubConnectorList.empty())
				{
					lhs = SingleCommandList.front();
					SingleCommandList.pop();
					rhs = SingleCommandList.front();
					SingleCommandList.pop();
					Connector = std::make_shared<Semicolon>(lhs, rhs);
					CommandTree.emplace_back(Connector);
				}
				else
				{
					lhs = SingleCommandList.front();
					SingleCommandList.pop();
					rhs = BuildTree(ConnectorList[i]->SubConnectorList);
					Connector = std::make_shared<Semicolon>(lhs, rhs);
					CommandTree.emplace_back(Connector);
				}
			}
			else
			{
				if (ConnectorList[i]->SubConnectorList.empty())
				{
					lhs = CommandTree.back();
					CommandTree.pop_back();
					rhs = SingleCommandList.front();
					SingleCommandList.pop();
					Connector = std::make_shared<Semicolon>(lhs, rhs);
					CommandTree.emplace_back(Connector);
				}
				else
				{
					lhs = CommandTree.back();
					CommandTree.pop_back();
					rhs = BuildTree(ConnectorList[i]->SubConnectorList);
					Connector = std::make_shared<Semicolon>(lhs, rhs);
					CommandTree.emplace_back(Connector);
				}
			}
		}
		else if (ConnectorList[i]->Type == "&&")
		{
			if (CommandTree.empty())
			{
				if (ConnectorList[i]->SubConnectorList.empty())
				{
					lhs = SingleCommandList.front();
					SingleCommandList.pop();
					rhs = SingleCommandList.front();
					SingleCommandList.pop();
					Connector = std::make_shared<And>(lhs, rhs);
					CommandTree.emplace_back(Connector);
				}
				else
				{
					lhs = SingleCommandList.front();
					SingleCommandList.pop();
					rhs = BuildTree(ConnectorList[i]->SubConnectorList);
					Connector = std::make_shared<And>(lhs, rhs);
					CommandTree.emplace_back(Connector);
				}
			}
			else
			{
				if (ConnectorList[i]->SubConnectorList.empty())
				{
					lhs = CommandTree.back();
					CommandTree.pop_back();
					rhs = SingleCommandList.front();
					SingleCommandList.pop();
					Connector = std::make_shared<And>(lhs, rhs);
					CommandTree.emplace_back(Connector);
				}
				else
				{
					lhs = CommandTree.back();
					CommandTree.pop_back();
					rhs = BuildTree(ConnectorList[i]->SubConnectorList);
					Connector = std::make_shared<And>(lhs, rhs);
					CommandTree.emplace_back(Connector);
				}
			}
		}
		else if (ConnectorList[i]->Type == "||")
		{
			if (CommandTree.empty())
			{
				if (ConnectorList[i]->SubConnectorList.empty())
				{
					lhs = SingleCommandList.front();
					SingleCommandList.pop();
					rhs = SingleCommandList.front();
					SingleCommandList.pop();
					Connector = std::make_shared<Or>(lhs, rhs);
					CommandTree.emplace_back(Connector);
				}
				else
				{
					lhs = SingleCommandList.front();
					SingleCommandList.pop();
					rhs = BuildTree(ConnectorList[i]->SubConnectorList);
					Connector = std::make_shared<Or>(lhs, rhs);
					CommandTree.emplace_back(Connector);
				}
			}
			else
			{
				if (ConnectorList[i]->SubConnectorList.empty())
				{
					lhs = CommandTree.back();
					CommandTree.pop_back();
					rhs = SingleCommandList.front();
					SingleCommandList.pop();
					Connector = std::make_shared<Or>(lhs, rhs);
					CommandTree.emplace_back(Connector);
				}
				else
				{
					lhs = CommandTree.back();
					CommandTree.pop_back();
					rhs = BuildTree(ConnectorList[i]->SubConnectorList);
					Connector = std::make_shared<Or>(lhs, rhs);
					CommandTree.emplace_back(Connector);
				}
			}
		}
		else if (ConnectorList[i]->Type == "|")
		{
			if (CommandTree.empty())
			{
				if (ConnectorList[i]->SubConnectorList.empty())
				{
					lhs = SingleCommandList.front();
					SingleCommandList.pop();
					rhs = SingleCommandList.front();
					SingleCommandList.pop();
					Connector = std::make_shared<Pipe>(lhs, rhs, "|");
					CommandTree.emplace_back(Connector);
				}
				else
				{
					lhs = SingleCommandList.front();
					SingleCommandList.pop();
					rhs = BuildTree(ConnectorList[i]->SubConnectorList);
					Connector = std::make_shared<Pipe>(lhs, rhs, "|");
					CommandTree.emplace_back(Connector);
				}
			}
			else
			{
				if (ConnectorList[i]->SubConnectorList.empty())
				{
					lhs = CommandTree.back();
					CommandTree.pop_back();
					rhs = SingleCommandList.front();
					SingleCommandList.pop();
					Connector = std::make_shared<Pipe>(lhs, rhs, "|");
					CommandTree.emplace_back(Connector);
				}
				else
				{
					lhs = CommandTree.back();
					CommandTree.pop_back();
					rhs = BuildTree(ConnectorList[i]->SubConnectorList);
					Connector = std::make_shared<Pipe>(lhs, rhs, "|");
					CommandTree.emplace_back(Connector);
				}
			}
		}	
		else if (ConnectorList[i]->Type == "<")
		{
			if (CommandTree.empty())
			{
				if (ConnectorList[i]->SubConnectorList.empty())
				{
					lhs = SingleCommandList.front();
					SingleCommandList.pop();
					rhs = SingleCommandList.front();
					SingleCommandList.pop();
					Connector = std::make_shared<InputRedirection>(lhs, rhs, "<");
					CommandTree.emplace_back(Connector);
				}
				else
				{
					lhs = SingleCommandList.front();
					SingleCommandList.pop();
					rhs = BuildTree(ConnectorList[i]->SubConnectorList);
					Connector = std::make_shared<InputRedirection>(lhs, rhs, "<");
					CommandTree.emplace_back(Connector);
				}
			}
			else
			{
				if (ConnectorList[i]->SubConnectorList.empty())
				{
					lhs = CommandTree.back();
					CommandTree.pop_back();
					rhs = SingleCommandList.front();
					SingleCommandList.pop();
					Connector = std::make_shared<InputRedirection>(lhs, rhs, "<");
					CommandTree.emplace_back(Connector);
				}
				else
				{
					lhs = CommandTree.back();
					CommandTree.pop_back();
					rhs = BuildTree(ConnectorList[i]->SubConnectorList);
					Connector = std::make_shared<InputRedirection>(lhs, rhs, "<");
					CommandTree.emplace_back(Connector);
				}
			}
		}		
		else if (ConnectorList[i]->Type == ">")
		{
			if (CommandTree.empty())
			{
				if (ConnectorList[i]->SubConnectorList.empty())
				{
					lhs = SingleCommandList.front();
					SingleCommandList.pop();
					rhs = SingleCommandList.front();
					SingleCommandList.pop();
					Connector = std::make_shared<OutputRedirection>(lhs, rhs, ">");
					CommandTree.emplace_back(Connector);
				}
				else
				{
					lhs = SingleCommandList.front();
					SingleCommandList.pop();
					rhs = BuildTree(ConnectorList[i]->SubConnectorList);
					Connector = std::make_shared<OutputRedirection>(lhs, rhs, ">");
					CommandTree.emplace_back(Connector);
				}
			}
			else
			{
				if (ConnectorList[i]->SubConnectorList.empty())
				{
					lhs = CommandTree.back();
					CommandTree.pop_back();
					rhs = SingleCommandList.front();
					SingleCommandList.pop();
					Connector = std::make_shared<OutputRedirection>(lhs, rhs, ">");
					CommandTree.emplace_back(Connector);
				}
				else
				{
					lhs = CommandTree.back();
					CommandTree.pop_back();
					rhs = BuildTree(ConnectorList[i]->SubConnectorList);
					Connector = std::make_shared<OutputRedirection>(lhs, rhs, ">");
					CommandTree.emplace_back(Connector);
				}
			}
		}
		else if (ConnectorList[i]->Type == ">>")
		{
			if (CommandTree.empty())
			{
				if (ConnectorList[i]->SubConnectorList.empty())
				{
					lhs = SingleCommandList.front();
					SingleCommandList.pop();
					rhs = SingleCommandList.front();
					SingleCommandList.pop();
					Connector = std::make_shared<OutputAppend>(lhs, rhs, ">>");
					CommandTree.emplace_back(Connector);
				}
				else
				{
					lhs = SingleCommandList.front();
					SingleCommandList.pop();
					rhs = BuildTree(ConnectorList[i]->SubConnectorList);
					Connector = std::make_shared<OutputAppend>(lhs, rhs, ">>");
					CommandTree.emplace_back(Connector);
				}
			}
			else
			{
				if (ConnectorList[i]->SubConnectorList.empty())
				{
					lhs = CommandTree.back();
					CommandTree.pop_back();
					rhs = SingleCommandList.front();
					SingleCommandList.pop();
					Connector = std::make_shared<OutputAppend>(lhs, rhs, ">>");
					CommandTree.emplace_back(Connector);
				}
				else
				{
					lhs = CommandTree.back();
					CommandTree.pop_back();
					rhs = BuildTree(ConnectorList[i]->SubConnectorList);
					Connector = std::make_shared<OutputAppend>(lhs, rhs, ">>");
					CommandTree.emplace_back(Connector);
				}
			}
		}		
	}

	CommandTree.clear();

	return Connector;
}