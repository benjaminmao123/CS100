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
        char* UserName = getlogin();
        
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
		
		if ((Input == ";" || Input == "&&" || Input == "||") && !HasConnector)
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
		while (!SingleCommandList.empty())
		{
			BuildTree();
		}
        
        while (!CommandTree.empty())
        {
            Invoker->SetCommand(CommandTree.front());
            Invoker->RunCommand();
            CommandTree.pop_front();
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

void Shell::BuildTree()
{
    if (SingleCommandList.size() > 1)
    {
        if (ConnectorList.front() == ";")
        {
			if (CommandTree.empty())
			{
				//get lhs and rhs to push into command tree
				//save first command as lhs to pass into a "semicolon" object
				std::shared_ptr<CommandBase> lhs = SingleCommandList.front();
				SingleCommandList.pop();
				//save second command as rhs to pass into a "semicolon" object
				std::shared_ptr<CommandBase> rhs = SingleCommandList.front();
				SingleCommandList.pop();

				//create "semicolon" object and push into tree
				Connector = std::make_shared<Semicolon>(lhs, rhs);
				CommandTree.emplace_front(Connector);

				//pop connector from queue
				ConnectorList.pop();
			}
			else
			{
				//get lhs and rhs to push into command tree
				//save first command as lhs to pass into a "semicolon" object
				std::shared_ptr<CommandBase> lhs = CommandTree.back();
				CommandTree.pop_back();
				//save second command as rhs to pass into a "semicolon" object
				std::shared_ptr<CommandBase> rhs = SingleCommandList.front();
				SingleCommandList.pop();

				//create "semicolon" object and push into tree
				Connector = std::make_shared<Semicolon>(lhs, rhs);
				CommandTree.emplace_front(Connector);

				//pop connector from queue
				ConnectorList.pop();
			}
        }
        //checks if the command is joined by an "and" operator
        else if (ConnectorList.front() == "&&")
        {
            //if tree is empty get lhs from SingleCommandList
            if (CommandTree.empty())
            {
                //save first command as lhs to pass into an "and" object
                std::shared_ptr<CommandBase> lhs = SingleCommandList.front();
                SingleCommandList.pop();
                //save second command as rhs to pass into an "and" object
                std::shared_ptr<CommandBase> rhs = SingleCommandList.front();
                SingleCommandList.pop();
                
                //create "and" object and push into tree
                Connector = std::make_shared<And>(lhs, rhs);
                CommandTree.emplace_front(Connector);
            }
            //if tree is not empty get lhs from back of tree
            else
            {
                //save first command as lhs to pass into an "and" object
                std::shared_ptr<CommandBase> lhs = CommandTree.back();
                CommandTree.pop_back();
                //save second command as rhs to pass into an "and" object
                std::shared_ptr<CommandBase> rhs = SingleCommandList.front();
                SingleCommandList.pop();
                
                //create "and" object and push into tree
                Connector = std::make_shared<And>(lhs, rhs);
                CommandTree.emplace_front(Connector);
            }
            
            //pop connector from queue
            ConnectorList.pop();
        }
        //checks if the command is joined by an "or" operator
        else if (ConnectorList.front() == "||")
        {
            //if tree is empty get lhs from SingleCommandList
            if (CommandTree.empty())
            {
                //save first command as lhs to pass into an "or" object
                std::shared_ptr<CommandBase> lhs = SingleCommandList.front();
                SingleCommandList.pop();
                //save second command as lhs to pass into an "or" object
                std::shared_ptr<CommandBase> rhs = SingleCommandList.front();
                SingleCommandList.pop();
                
                //create "or" object and push into tree    
                Connector = std::make_shared<Or>(lhs, rhs);
                CommandTree.emplace_front(Connector);
            }
            //if tree is not empty get lhs from back of tree
            else
            {
                //get lhs from back of commandtree
                std::shared_ptr<CommandBase> lhs = CommandTree.back();
                CommandTree.pop_back();
                //save second command as rhs to pass into an "or" object
                std::shared_ptr<CommandBase> rhs = SingleCommandList.front();
                SingleCommandList.pop();
                
                //create "or" object and push into tree    
                Connector = std::make_shared<Or>(lhs, rhs);
                CommandTree.emplace_front(Connector);
            }
            
            //pop connector from queue
            ConnectorList.pop();
        }
    }
    //get lhs from back of commandtree
    else
    {
        if (ConnectorList.front() == ";")
        {
            //get lhs and rhs to push into command tree
            //save back of commandtree as lhs to pass into a "semicolon" object
            std::shared_ptr<CommandBase> lhs = CommandTree.back();
            CommandTree.pop_back();
            //save second command as rhs to pass into a "semicolon" object
            std::shared_ptr<CommandBase> rhs = SingleCommandList.front();
            SingleCommandList.pop();
            
            //create "semicolon" object and push into tree
            Connector = std::make_shared<Semicolon>(lhs, rhs);
            CommandTree.emplace_front(Connector);
            
            //pop connector from queue
            ConnectorList.pop();
        }
        //checks if the command is joined by an "and" operator
        else if (ConnectorList.front() == "&&")
        {
            //get lhs from back of commandtree
            std::shared_ptr<CommandBase> lhs = CommandTree.back();
            CommandTree.pop_back();
            //save second command as rhs to pass into an "and" object
            std::shared_ptr<CommandBase> rhs = SingleCommandList.front();
            SingleCommandList.pop();
            
            //create "and" object and push into tree
            Connector = std::make_shared<And>(lhs, rhs);
            CommandTree.emplace_front(Connector);
            
            //pop connector from queue
            ConnectorList.pop();
        }
        //checks if the command is joined by an "or" operator
        else if (ConnectorList.front() == "||")
        {
            //get lhs from back of commandtree
            std::shared_ptr<CommandBase> lhs = CommandTree.back();
            CommandTree.pop_back();
            //save second command as rhs to pass into an "or" object
            std::shared_ptr<CommandBase> rhs = SingleCommandList.front();
            SingleCommandList.pop();
            
            //create "or" object and push into tree
            Connector = std::make_shared<Or>(lhs, rhs);
            CommandTree.emplace_front(Connector);
            
            //pop connector from queue
            ConnectorList.pop();
        }
    }
}