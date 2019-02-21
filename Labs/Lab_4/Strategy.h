#pragma once

#include "Composite.h"
#include "BaseFactory.h"

#include <iostream>
#include <stdexcept>

class Sort;
class Container;

class Sort
{
public:
	/* Constructors */
	Sort()
	{

	}
	/* Pure Virtual Functions */
	virtual void sort(Container *container) = 0;
};

class Container
{
protected:
	Sort *sort_function;
	BaseFactory *Print;

public:
	/* Constructors */
	Container() : sort_function(NULL), Print(NULL) { }
	Container(Sort *function, BaseFactory *factory) : sort_function(function), Print(factory) { }
	/* Non Virtual Functions */
	// Set the type of sorting algorithm
	void set_sort_function(Sort *sort_function)
	{
		this->sort_function = sort_function;
		
		if (this->sort_function == NULL)
		{
			throw std::invalid_argument("sort_function is NULL");
		}
	}
	
	void set_print_function(BaseFactory *Print)
	{
		this->Print = Print;
	}
	/* Pure Virtual Functions */
	// insert the top pointer of the tree into the container											
	virtual void add_element(Base *element) = 0;
	// iterate through trees and output values
	virtual void print() const = 0;
	// calls on the previously set sorting-algorithm. Checks if sort_function is not null, throw exception if otherwise
	virtual void sort() = 0;
	/* Essentially the only functions needed to sort */
	// switch tree locations
	virtual void swap(int i, int j) = 0;
	// get the top pointer of tree at index i
	virtual Base * at(int i) const = 0;
	// return the container size
	virtual unsigned int size() const = 0;
};

class SelectionSort : public Sort
{
public:
	void sort(Container *container)
	{
		if (!container->size())
		{
			return;
		}
		
		unsigned int j;

		for (unsigned int i = 0; i < container->size(); ++i)
		{
			unsigned int minVal = i;

			for (j = i + 1; j < container->size(); ++j)
			{
				if (container->at(j)->evaluate() < container->at(minVal)->evaluate())
				{
					minVal = j;
				}
			}

			container->swap(i, minVal);
		}
	}
};

class BubbleSort : public Sort
{
public:
	void sort(Container *container)
	{
		if (!container->size())
		{
			return;
		}
		
		for (unsigned int i = 0; i < container->size() - 1; ++i)
		{
			for (unsigned int j = 0; j < container->size() - i - 1; ++j)
			{
				if (container->at(j)->evaluate() > container->at(j + 1)->evaluate())
				{
					container->swap(j, j + 1);
				}
			}
		}
	}
};