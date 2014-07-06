/*
C++ Copy Constructor Example
Kyle Ross
2/7/2014
*/
#include "SomeClass.h"

SomeClass::SomeClass()
{
	this->someString = "I'm a blank object.";
}

SomeClass::SomeClass(string someString)
{
	//Randomly throw an exception
	if( (rand() % 4 + 1) == 1)
		throw exception("Specific Constructor Failed! Some exception fired!");

	this->someString = someString;
	cout << "I'm a temporary object made from a specific constructor" << endl;
}

SomeClass::SomeClass(const SomeClass& someObject)
{
	//If SomeClass was passed in by value and not constant reference,
	//The compiler will make a temporary object
	//If that object is a constant stream, like a file, the code cannot compile
	//Because a constant stream doesn't expose a copy constructor
	this->someString = someObject.someString + " Copied";
	cout << "I'm a temporary object created from some object by constant reference" << endl;
}

SomeClass& SomeClass::operator=(const SomeClass& someObject)
{
	//Copy the properties from the temporary Constructed object
	this->someString = someObject.someString;
	cout << "Copying the temporary object's properties back into constant reference" << endl << endl;
	
	//Return the reference to this object, In order to chain these operators 
	//(Return value and Parameters are same Data type)
	return *this;
}

ostream& operator<<(ostream& out, SomeClass& someObject)
{
	out << someObject.someString << endl;
	out << "Printed Some Overloaded Object" << endl;
	return out;
}