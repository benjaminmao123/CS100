#pragma once

#include <vector>
#include <string>
#include <unistd.h>
#include <cstdio>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <cstdlib>
#include <iostream>

class CommandReceiver
{
public:
    void Terminate() const;
    bool RunProgram(std::vector<std::string> &ArgumentList, int fdin, int fdout) const;
    bool ChangeDirectory(std::vector<std::string> &ArgumentList) const;
    bool Test(std::vector<std::string> &ArgumentList, const int fdout) const;
};