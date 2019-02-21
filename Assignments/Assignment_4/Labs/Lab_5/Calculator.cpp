#include "Menu.h"
#include "Command.h"

#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

bool isInteger(const string &s)
{
	if (s.empty())
	{
		return false;
	}

	char *p;
	strtol(s.c_str(), &p, 10);

	return (*p == 0);
}

int main() 
{
	Menu *menu = new Menu();
	string input;

	while (input != "exit") 
	{

		cout << "Choose a Menu Command: ";
		getline(cin, input);		

		if (input == "exit") 
		{
			break;
		}
		else if (input == "redo") 
		{
			cout << "Redoing Command" << endl;
			menu->redo();	
			cout << "Result: ";
			menu->execute();
		}
		else if (input == "undo") 
		{
			cout << "Undoing Command" << endl;
			menu->undo();
			cout << "Result: ";
			menu->execute();
		}
		else if (isInteger(input)) 
		{
			if (!menu->initialized()) 
			{
				menu->add_command(new OpCommand(atoi(input.c_str())));
				cout << "Result: ";
				menu->execute();
			}
		}
		else if (input.substr(0, 1) == "+") 
		{
			if (menu->initialized()) 
			{
				if (isInteger(input.substr(2))) 
				{
					menu->add_command(new AddCommand(menu->get_command(), atoi((input.substr(2)).c_str())));
					cout << "Result: ";
					menu->execute();
				}
			}
		}
		else if (input.substr(0, 1) == "-") 
		{
			if (menu->initialized()) 
			{
				if (isInteger(input.substr(2))) 
				{
					menu->add_command(new SubCommand(menu->get_command(), atoi((input.substr(2)).c_str())));
					cout << "Result: ";
					menu->execute();
				}
			}
		}
		else if (input.substr(0, 1) == "*") 
		{
			if (menu->initialized()) 
			{
				if (isInteger(input.substr(2))) 
				{
					menu->add_command(new MultCommand(menu->get_command(), atoi((input.substr(2)).c_str())));
					cout << "Result: ";
					menu->execute();
				}
			}
		}
		else if (input == "^")
		{
			if (menu->initialized()) 
			{
				menu->add_command(new SqrCommand(menu->get_command()));
				cout << "Result: ";
				menu->execute();
			}
		}
		else 
		{
			cout << "Invalid Command" << endl;
		}
	}
};
