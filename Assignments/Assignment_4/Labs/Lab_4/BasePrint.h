#include <iostream>
#include <bitset>

class BasePrint 
{
public:
	/* Constructors */
	BasePrint() : value(0)
	{
		
	}
	
	BasePrint(double value) : value(value)
	{
		
	}
	
	/* Pure Virtual Print Function */
	virtual void print() = 0;
protected:
	/* Value to Print */
	double value;
};

class DoublePrint : public BasePrint
{
public:
    DoublePrint(double value) : BasePrint(value)
    {
    	
    }
    
    void print()
    {
    	std::cout << value;
    }
};

class HexPrint : public BasePrint
{
public:
    HexPrint(double value) : BasePrint(value)
    {
    	
    }
   
    void print()
    {
    	std::cout << std::hexfloat << value; //std::hexfloat
    }
};

class BinaryPrint : public BasePrint
{
public:
    BinaryPrint(double value) : BasePrint(value)
    {
    	
    }
    
    void print()
    {
    	std::bitset<16> bits(value);
    	
    	std::cout << bits;
    }
};