#include "BasePrint.h"

#include <string>

class BaseFactory 
{
public:
	/* Constructor */
	BaseFactory()
	{

	}
    
	/* Pure Virtual Generate Function */
    virtual	BasePrint * generatePrint(double value) = 0;
};

class DoubleFactory : public BaseFactory
{
public:
    DoubleFactory()
    {
        
    }
    
    BasePrint * generatePrint(double value)
    {
        BasePrint *Print = new DoublePrint(value);
        return Print;
    }
};

class HexFactory : public BaseFactory
{
public:
    HexFactory()
    {
        
    }
    
    BasePrint * generatePrint(double value)
    {
        BasePrint *Print = new HexPrint(value);
        return Print;
    }
};

class BinaryFactory : public BaseFactory
{
public:
    BinaryFactory()
    {
        
    }
    
    BasePrint * generatePrint(double value)
    {
        BasePrint *Print = new BinaryPrint(value);
        return Print;
    }
};