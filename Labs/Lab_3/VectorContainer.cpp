#include "VectorContainer.h"

#include <algorithm>

void VectorContainer::add_element(Base *element)
{
	tree.push_back(element);
}

void VectorContainer::print() const
{
	if (tree.size())
	{
		for (const auto &i : tree)
		{
			BasePrint *BP = Print->generatePrint(i->evaluate());
			BP->print();
			std::cout << " ";
		}
	}
}

void VectorContainer::sort()
{
	sort_function->sort(this);
}

void VectorContainer::swap(int i, int j)
{
	std::swap(tree[i], tree[j]);
}

Base * VectorContainer::at(int i) const
{
	return tree.at(i);
}

unsigned int VectorContainer::size() const
{
	return tree.size();
}
