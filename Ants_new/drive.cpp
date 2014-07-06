#include <iostream>
#include "World.h"
#include "Ant.h"
using namespace std;

int main()
{
	World world = World();
	Ant ant = Ant();
	ant.move();
	cin.get();
	return 0;
}
