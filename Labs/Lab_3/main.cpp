#include "VectorContainer.h"
#include "ListContainer.h"
#include "Decorator.h"

#include <iostream>
#include <cstring>

using namespace std;

int main()
{
	VectorContainer *v = new VectorContainer();
	ListContainer *l = new ListContainer();
	
	Operand *Op1 = new Operand(1);
	Operand *Op2 = new Operand(2);
	Operand *Op3 = new Operand(3);

	Add *add = new Add(Op1, Op2);

	cout << "Add: " << add->evaluate() << endl;
	v->add_element(add);
	l->add_element(add);

	Subtract *subtract = new Subtract(add, Op3);

	cout << "Subtract: " << subtract->evaluate() << endl;
	v->add_element(subtract);
	l->add_element(subtract);
	
	Multiply *multiply = new Multiply(add, subtract);

	cout << "Multiply: " << multiply->evaluate() << endl;
	v->add_element(multiply);
	l->add_element(multiply);

	Divide *divide = new Divide(multiply, subtract);

	cout << "Divide: " << divide->evaluate() << endl;
	v->add_element(divide);
	l->add_element(divide);
	
	Square *square = new Square(divide);

	cout << "Square: " << square->evaluate() << endl;
	v->add_element(square);
	l->add_element(square);

	cout << "Vector Before Selection Sort: " << endl;
	v->print();
	cout << endl;

	cout << "Vector After Selection Sort: " << endl;
	v->set_sort_function(new SelectionSort());
	v->sort();
	v->print();
	cout << endl;

	cout << "List Before Bubble Sort: " << endl;
	l->print();
	cout << endl;

	cout << "List After Bubble Sort: " << endl;
	l->set_sort_function(new BubbleSort());
	l->sort();
	l->print();
	cout << endl;

	Base *number = new Add(new Operand(-6.3), new Operand(-1.2));

	cout << "Before Ceiling: " << endl;
	cout << number->evaluate() << endl;
	
	number = new Ceiling(new Add(new Operand(-6.3), new Operand(-1.2)));

	cout << "After Ceiling: " << endl;
	cout << number->evaluate() << endl;

	cout << "Before Floor: " << endl;
	cout << number->evaluate() << endl;
	
	number = new Ceiling(new Floor(new Add(new Operand(-6.3), new Operand(-1.2))));

	cout << "After Floor: " << endl;
	cout << number->evaluate() << endl;

	cout << "Before Absolute Value: " << endl;
	cout << number->evaluate() << endl;

	number = new AbsoluteValue(new Ceiling(new Floor(new Add(new Operand(-6.3), new Operand(-1.2)))));

	cout << "After Absolute Value: " << endl;
	cout << number->evaluate() << endl;

	return 0;
}