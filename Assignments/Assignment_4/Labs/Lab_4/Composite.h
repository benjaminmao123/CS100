#pragma once

class Base
{
public:
	/* Constructors */
	Base() 
	{ 
		
	}
	/* Pure Virtual Functions */
	virtual double evaluate() = 0;
};

class Operand : public Base
{
public:
	Operand(double number)
	{
		this->number = number;
	}

	double evaluate()
	{
		return number;
	}

private:
	double number;
};

class Operator : public Base
{
public:
	Operator(Base *lhs, Base *rhs)
	{
		this->lhs = lhs;
		this->rhs = rhs;
	}

	virtual double evaluate() = 0;

protected:
	Base *lhs;
	Base *rhs;
};

class UnaryOperator : public Base
{
public:
	UnaryOperator(Base *Op)
	{
		this->Op = Op;
	}

	virtual double evaluate() = 0;

protected:
	Base *Op;
};

class Add : public Operator
{
public:
	Add(Base *lhs, Base *rhs) : Operator(lhs, rhs)
	{
		
	}

	double evaluate()
	{
		return lhs->evaluate() + rhs->evaluate();
	}
};

class Subtract : public Operator
{
public:
	Subtract(Base *lhs, Base *rhs) : Operator(lhs, rhs)
	{

	}

	double evaluate()
	{
		return lhs->evaluate() - rhs->evaluate();
	}
};

class Multiply : public Operator
{
public:
	Multiply(Base *lhs, Base *rhs) : Operator(lhs, rhs)
	{

	}

	double evaluate()
	{
		return lhs->evaluate() * rhs->evaluate();
	}

};

class Divide : public Operator
{
public:
	Divide(Base *lhs, Base *rhs) : Operator(lhs, rhs)
	{

	}

	double evaluate()
	{
		return lhs->evaluate() / rhs->evaluate();
	}
};

class Square : public UnaryOperator
{
public:
	Square(Base *Op) : UnaryOperator(Op)
	{

	}

	double evaluate()
	{
		return Op->evaluate() * Op->evaluate();
	}
};