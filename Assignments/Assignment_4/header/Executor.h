#include <string>
#include <vector>

class Command;

class Executor
{
public:
    bool operator()(const std::vector<Command*>& postfix);

private:
    std::vector<Command*> ptrs;
};