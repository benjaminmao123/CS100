# Abstract Factory Pattern
## Author: Brian Crites
**You *must* work in a group of two for this lab**

In the previous strategy lab you wrote a function ```void print()``` that iterated through the collections of equations trees and prints their ```double evaluation()``` values. In this lab you will extend that functionality to allow for printing of the ```double evaluation()``` values in several different formats. You first task is to create three new classes for printing the values as a double (```class DoublePrint```), as hex values (```class HexPrint```) and as a binary number (```class BinaryPrint```). All of these classes will inherit from a new abstract base class for printing (```class BasePrint```).
```c++
class BasePrint {
	private:
		/* Value to Print */
		double value;

	public:
		/* Constructors */
		BasePrint();
		BasePrint(double value);
		
		/* Pure Virtual Print Function */
		virtual void print() = 0;
}
```
Once you have created **and commited** the base class ```BasePrint```, you can create the other printing classes. Each class should be created independently and be thoroughly test before moving on. **Each class should be it’s own commit** with a proper commit message. 
* ```DoublePrint``` will simply print the values of the object like you normally would
* For ```HexPrint``` you will need to utilize the [hex printing feature of iostream](http://www.cplusplus.com/reference/ios/hexfloat/) (note that to utilize the hex printing library, you will have to compile it in c++11 using the ```-std=c++11``` compiler flag). 
* For ```BinaryPrint``` you will need to utilize the [bitset library](http://www.cplusplus.com/reference/bitset/bitset/?kw=bitset) and use the value to create a bitset object for the value that is then printed. 

**Testing Point:** You should create a short test program that instantiates each of the ```BasePrint``` concrete subclasses and calls ```void print()``` on them to make sure your classes are working correctly. This program will evolve as you create more print methods. The test program should be present in all of your commits. You want to test as you go, not wait until the end to test. 

Once you have created these printing objects and tested them you will create a set of factories to guarantee that the same printing method is used throughout your program. Start by creating an abstract base factory class (```class BaseFactory```).
```c++
class BaseFactory {
	public:
		/* Constructor */
		BaseFactory();

		/* Pure Virtual Generate Function */
		BasePrint* generatePrint(double value) = 0;
}
```
From here you will create a factory for each type of printer that was created (```DoubleFactory```, ```HexFactory```, ```BinaryFactory```). Each concrete factory should be developed independently and thoroughly test before moving on. **Each should have it’s own commit** with a proper commit message. These concrete factories will have their ```BasePrint* generatePrint(double value)``` function overwritten to return the correct print object for that particular factory.

**Testing Point:** You should create a short test program that instantiates each type of ```BaseFactory``` concrete subclass, generates print objects from each, and then prints each generated object to very that your classes are working correctly. The test program should be present in all of your commits. You want to test as you go, not wait until the end to test. 

Once you have created all the necessary factories and tested them, you will need to modify the ```Container``` class to utilize the new factory and printing objects. First you will need to extend the current constructors for the ```Container``` class to also accept a ```BaseFactory*```, and save that pointer as a member of the ```Container``` class. From there you can re-write the ```void print()``` function so that it first generates a print object from the ```Container```’s internal factory, and then calls print on that factory (rather than calling print on the evaluation directly). You will want to make a commit for each container when you modify them. 

Once you have re-written the ```void print()``` function for the ```Container``` class, you can update your program to put all of these elements together. Starting with the test program from the strategy lab (or the test program provided in the strategy lab if you didn’t write one), add command line arguments to the program. You program will take in a single command line argument, which will be either the letter ```d```, ```h```, or ```b```. These letters (flags) will be parsed at the beginning of your program and determine what type of printing your program will utilize. The first thing in your program must be parsing the command line flag and setting a single factory to the correct type. Once that factory has been set, you should pass it to all of your containers for use in printing. You should commit these changes once they are working.

Flag | Printing
------------ | ------------
d | Set the single factory to a ```DoubleFactory```
h | Set the single factory to a ```HexFactory```
b | Set the single factory to a ```BinaryFactory```

## Submission
To receive credit for this lab you must show an example program to your TA that demonstrates the full functionality of this pattern, and must explain to your TA the structure of your abstract factory pattern.

Make sure your code has been fully merged and the master branch has been committed and pushed to github. Submit to ilearn a screenshot of your github push. 
