#pragma once

#include "Strategy.h"

#include <vector>

class VectorContainer : public Container
{
public:
	void add_element(Base *element) override;
	void print() const override;
	void sort() override;
	void swap(int i, int j) override;
	Base * at(int i) const override;
	unsigned int size() const override;

private:
	Base *element;
	std::vector<Base *> tree;
};