#include <iostream>

#include "../header/Shell.h"
#include "../header/Command.h"
#include "../header/ErrorLibrary.h"

void Shell::Run()
{
    while (true)
    {
        Clear();
        PrintCommandPrompt();
        GetCommand();
        
        if (!command.empty() &&
            command.find_first_not_of(' ') != std::string::npos)
        {
            ParseCommand();
            ExecuteCommand();    
        }
    }
}

void Shell::PrintCommandPrompt() const
{
    std::cout << "$ ";
}

void Shell::GetCommand()
{
    std::getline(std::cin, command);
}

void Shell::ParseCommand()
{
    postfix = parser(command);
}

void Shell::ExecuteCommand()
{
    if (postfix.empty())
    {
        std::cout << "Error: " << 
            ErrorLibrary::GetErrorMessage() << std::endl;
        
        ErrorLibrary::state = ErrorLibrary::ErrorState::NONE;
        
        return;
    }
    
    executor(postfix);

    for (const auto& i : postfix)
        delete i;
}

void Shell::Clear()
{
    command.clear();
    postfix.clear();
}