#include "composite.h"

using namespace std;

OperatorIterator::OperatorIterator(Base * ptr) : Iterator(ptr)
{

}

void OperatorIterator::first()
{
	current_ptr = self_ptr->get_left();
}

void OperatorIterator::next()
{
	if (current_ptr == self_ptr->get_right())
	{
		current_ptr = nullptr;
		return;
	}

	current_ptr = self_ptr->get_right();
}

bool OperatorIterator::is_done()
{
	return current_ptr == nullptr;
}

Base * OperatorIterator::current()
{
	return current_ptr;
}

UnaryIterator::UnaryIterator(Base* ptr) : Iterator(ptr)
{

}

void UnaryIterator::first()
{
	current_ptr = self_ptr->get_left();
}

void UnaryIterator::next()
{
	current_ptr = nullptr;
}

bool UnaryIterator::is_done()
{
	return current_ptr == nullptr;
}

Base * UnaryIterator::current()
{
	return current_ptr;
}

NullIterator::NullIterator(Base * ptr) : Iterator(ptr)
{

}

void NullIterator::first()
{

}

void NullIterator::next()
{

}

bool NullIterator::is_done()
{
	return true;
}

Base * NullIterator::current()
{
	return current_ptr;
}

PreOrderIterator::PreOrderIterator(Base *ptr) : Iterator(ptr)
{

}

void PreOrderIterator::first() 
{
    // Empty the Iterators (just in case we had something leftover from another run)
    // Create an iterator for the Base* that we built the iterator for
    // Initialize that iterator and push it onto the Iterators
	std::stack<Iterator *>().swap(Iterators);

	Iterator *iter = self_ptr->create_iterator();
	iter->first();
	Iterators.push(iter);
}

void PreOrderIterator::next() 
{
    // Create an iterator for the item on the top of the Iterators
    // Initialize the iterator and push it onto the Iterators
    // As long as the top iterator on the Iterators is_done(), pop it off the Iterators and then advance whatever iterator is now on top of the Iterators
	if (!Iterators.empty())
	{
		Iterator *iter = Iterators.top()->current()->create_iterator();
		iter->first();
		Iterators.push(iter);

		while (!Iterators.empty() && Iterators.top()->is_done())
		{
			Iterators.pop();

			if (!Iterators.empty())
			{
				Iterators.top()->next();
			}
		}
	}
}

bool PreOrderIterator::is_done() 
{
    // Return true if there are no more elements on the Iterators to iterate
	return Iterators.empty();
}

Base * PreOrderIterator::current() 
{
    // Return the current for the top iterator in the Iterators
	return Iterators.top()->current();
}
