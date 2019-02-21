#ifndef __MENU_CLASS__
#define __MENU_CLASS__

#include "Command.h"

#include <iostream>
#include <vector>

using namespace std;

class Menu 
{
public:
	Menu() : history_index(0), history(1)
	{
		//Base constructor to set up all necessary members
	}
	
	void execute() 
	{
		//Prints the current commands value (based on history_index), if no commands exist
		//print 0 by default
		if (!history_index)
		{
			cout << "0\n";
		}
		else
		{
			cout << history[history_index]->execute() << "\n";
		}
	}
	
	bool initialized() 
	{
		//Return true if the history has been primed with a single op instruction
		//This is necessary because that is the base of a calculation
		return (history.size() == 1) ? false : true;
	}
	
	void add_command(Command *cmd) 
	{
		//Adds a command to history in the appropriate posiiton (based on history_index)
		if (history_index == history.size())
		{
			history.emplace_back(cmd);
		}
		else if ((history.size() - history_index) == 1)
		{
			history.emplace_back(cmd);
			++history_index;
		}
		else
		{
			++history_index;
			history[history_index] = cmd;
		}
	}
	
	Command * get_command() 
	{
		//Returns the command in history we are currently referring to (based on history_index)
		if (!history.empty())
		{
			return history[history_index];
		}
		
		return nullptr;
	}
	
	void undo() 
	{
		//Moves to the last command in history (if possible)
		if (history_index)
		{
			--history_index;
		}
	}
	
	void redo() 
	{
		//Moves to the next command in history (if possible)
		if ((history_index + 1) < history.size())
		{
			++history_index;
		}
	}
	
private:
	unsigned int history_index;
	vector<Command *> history;
};

#endif //__MENU_CLASS__
