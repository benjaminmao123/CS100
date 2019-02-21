#include "VectorContainer.h"
#include "ListContainer.h"
#include "Decorator.h"

#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
	BaseFactory *p;
	
	if (argc != 2)
	{
		std::cout << "Requires one argument.\n";
		exit(EXIT_FAILURE);
	}
	else
	{
		if (!strcmp(argv[1], "d"))
		{
			p = new DoubleFactory();
		}
		else if (!strcmp(argv[1], "h"))
		{
			p = new HexFactory();
		}
		else if (!strcmp(argv[1], "b"))
		{
			p = new BinaryFactory();
		}
		else
		{
			std::cout << "Invalid argument. Valid inputs are 'd', 'h', or 'b'.\n";
			exit(EXIT_FAILURE);
		}
	}

	Container *vector = new VectorContainer();
	Container *list = new ListContainer();
	
	vector->set_print_function(p);
	list->set_print_function(p);

	vector->add_element(new Operand(1));
	vector->add_element(new Operand(2));
	vector->add_element(new Operand(3));
	vector->add_element(new Operand(4));
	vector->add_element(new Operand(5));

	list->add_element(new Operand(1));
	list->add_element(new Operand(2));
	list->add_element(new Operand(3));
	list->add_element(new Operand(4));
	list->add_element(new Operand(5));

	std::cout << "Vector: ";
	vector->print();
	
	std::cout << "\nList: ";
	list->print();
	
	std::cout << endl;

	return 0;
}