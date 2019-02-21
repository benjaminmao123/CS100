#include "ListContainer.h"

#include <stdexcept>

void ListContainer::add_element(Base *element)
{
	tree.push_back(element);
}

void ListContainer::print() const
{
	if (tree.size())
	{
		for (auto &i : tree)
		{
			BasePrint *BP = Print->generatePrint(i->evaluate());
			BP->print();
			std::cout << " ";
		}
	}
}

void ListContainer::sort()
{
	sort_function->sort(this);
}

void ListContainer::swap(int i, int j)
{
	int counti = 0;
	int countj = 0;

	Base *temp1, *temp2;

	for (auto &k : tree)
	{
		if (counti == i)
		{
			temp1 = k;
		}

		if (countj == j)
		{
			temp2 = k;
		}

		++counti, ++countj;
	}

	counti = countj = 0;

	for (auto &k : tree)
	{
		if (counti == i)
		{
			k = temp2;
		}

		if (countj == j)
		{
			k = temp1;
		}

		++counti, ++countj;
	}
}

Base * ListContainer::at(int i) const
{
	if (i >= static_cast<int>(tree.size()) || i < 0)
	{
		throw std::out_of_range("ListContainer::at_range_check");
	}
	
	for (const auto &k : tree)
	{
		if (!i)
		{
			return k;
		}
		
		--i;
	}
	
	return nullptr;
}

unsigned int ListContainer::size() const
{
	return tree.size();
}