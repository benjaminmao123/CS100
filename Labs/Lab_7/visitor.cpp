#include "visitor.h"

PrintVisitor::PrintVisitor()
{
    
}

void PrintVisitor::rootNode()
{
    
}

void PrintVisitor::sqrNode()
{
    output += "^";
}

void PrintVisitor::multNode()
{
    output += "*";
}

void PrintVisitor::subNode()
{
    output += "-";
}

void PrintVisitor::addNode()
{
    output += "+";
}

void PrintVisitor::opNode(Op *op)
{
    double value = op->evaluate();
    output += " ";
    output += to_string(value);
    output += " ";
}

void PrintVisitor::execute()
{
    cout << output << endl;
}