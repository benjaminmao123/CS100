#pragma once
#include "composite.h"

class Op;

class Visitor
{
public:
	virtual void rootNode() = 0;	//For visiting a root node (do nothing)
	virtual void sqrNode() = 0;		//For visiting a square node
	virtual void multNode() = 0;	//For visiting a multiple node
	virtual void subNode() = 0;		//For visiting a subtraction node
	virtual void addNode() = 0;		//For visiting an add node
	virtual void opNode(Op* op) = 0;	//For visiting a leaf node
	virtual void execute() = 0;		//Prints all visited nodes
};

class PrintVisitor : public Visitor
{
public:
	PrintVisitor();

	void rootNode();	//For visiting a root node (do nothing)
	void sqrNode();		//For visiting a square node
	void multNode();	//For visiting a multiple node
	void subNode();		//For visiting a subtraction node
	void addNode();		//For visiting an add node
	void opNode(Op* op);	//For visiting a leaf node
	void execute();		//Prints all visited nodes
	
private:
	std::string output;
};
