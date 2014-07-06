/*
C++ Copy Constructor Example
Kyle Ross
2/7/2014
*/
#include "SomeClass.h"
using namespace std;

int main()
{
	while(true)
	{
		//Create a blank object
		//This calls the default Constructor
		SomeClass someObject;
		SomeClass anotherObject;
		string someString = "Some String";

		//Print the blank object
		cout << someObject << endl;

		//Try and re-create someObject with a specific constructor
		try
		{
			//Create a temporary nameless Object by calling SomeClass(someString)
			//Then use someObject's operator= to copy that nameless object's properties
			someObject = SomeClass(someString);

			cout << someObject << endl;
			
			//Copy Constructor is used with arguments of constant reference
			//Such as any stream object like a file or cout
			//Copy someObject by constant reference
			anotherObject = SomeClass(someObject);

			cout << anotherObject << endl;
		}
		catch(exception e)
		{
			cout << e.what() << endl << endl;
		}
		
		//The above would all be needed to use someObject out of try/catch scope
		cin.get();
	}
	return 0;
}