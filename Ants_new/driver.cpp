#include <iostream>
#include "World.h"
#include "Ant.h"
using namespace std;

int main()
{
	Ant ant = Ant();
	ant.move();
	cout << ant << endl;
	cin.get();
	return 0;
}
