#ifndef __COMMAND_CLASS__
#define __COMMAND_CLASS__

#include "Composite.h"

class Command 
{
public:
	Command()
	{ 
		
	}
	
	double execute() 
	{
		return root->evaluate();
	}
	
	Base * get_root() 
	{
		return root;
	}
	
protected:
	Base *root;
};

class OpCommand : public Command 
{
public:
	OpCommand(double Value)
	{
		root = new Operand(Value);
	}
};

class AddCommand : public Command 
{
public:
	AddCommand(Command *Cmd, double Value)
	{
		root = new Add(Cmd->get_root(), new Operand(Value));
	}
};

class SubCommand : public Command 
{
public:
	SubCommand(Command *Cmd, double Value) 
	{
		root = new Subtract(Cmd->get_root(), new Operand(Value));
	}
};

class MultCommand : public Command 
{
public:
	MultCommand(Command *Cmd, double Value)
	{
		root = new Multiply(Cmd->get_root(), new Operand(Value));
	}
};

class SqrCommand : public Command 
{
public:
	SqrCommand(Command *Cmd) 
	{
		root = new Square(Cmd->get_root());
	}
};

#endif //__COMMAND_CLASS__
