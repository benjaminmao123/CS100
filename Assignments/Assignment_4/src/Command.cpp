#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "../header/Command.h"

Command::Command(TokenType type,
    const std::vector<std::string>& args,
    Command* lhs,
    Command* rhs) :
    Token(type, lhs, rhs),
    args(args),
    fdin(STDIN_FILENO),
    fdout(STDOUT_FILENO)
{ }

Command::Command(TokenType type, 
    Command* lhs, 
    Command* rhs) :
    Command(type, std::vector<std::string>(), lhs, rhs)
{ }

Command::~Command()
{ }

bool Command::Execute()
{
    if (args.empty())
        return false;

    std::vector<char*> args;

    for (const auto& token : GetArgs())
        args.emplace_back(const_cast<char*>(token.c_str()));

    args.emplace_back(nullptr);

    pid_t pid = fork();

    if (pid > 0)
    {
        int status;

        if (waitpid(pid, &status, 0) == -1)
        {
            perror("wait");

            return false;
        }

        if (WEXITSTATUS(status))
            return false;
    }
    else if (!pid)
    {
        int oldfdout = dup(1);
        
        if (dup2(fdin, STDIN_FILENO) == -1)
        {
            perror("dup2");
            
            return false;
        }
        
        if (dup2(fdout, STDOUT_FILENO) == -1)
        {
            perror("dup2");
            
            return false;
        }		
        
        if (execvp(args[0], args.data()) == -1)
        {
            dup2(oldfdout, STDOUT_FILENO);
            
            std::cout << "Shell: " << args[0] << ": " << "command not found" << std::endl;

            exit(EXIT_FAILURE);
        }
    }
    else
    {
        perror("fork");

        return false;
    }

    return true;
}

void Command::SetArgs(const std::vector<std::string>& args)
{
    this->args = args;
}

const std::vector<std::string>& Command::GetArgs() const
{
    return args;
}

int Command::In() const
{
    return fdin;
}

void Command::In(int value)
{
    fdin = value;
}

int Command::Out() const
{
    return fdout;	
}

void Command::Out(int value)
{
    fdout = value;
}