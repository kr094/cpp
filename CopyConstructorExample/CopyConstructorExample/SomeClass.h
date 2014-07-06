/*
C++ Copy Constructor Example
Kyle Ross
2/7/2014
*/
#ifndef _SOME_CLASS_H_
#define _SOME_CLASS_H_
#include <iostream>
#include <string>
using namespace std;
class SomeClass
{
private:
	string someString;
public:
	//Default
	SomeClass();
	//Specific
	SomeClass(string someString);
	//Copy
	SomeClass(const SomeClass& someObject);
	
	//Overloaded assignment operator
	//This is normally created by the compiler
	SomeClass& operator=(const SomeClass& someObject);

	//Overloaded Output Operator
	friend ostream& operator<<(ostream& out, SomeClass& someObject);
};

#endif