#include "World.h"

World::World()
{
//	//this->__world = new Organism**[_WORLD_HEIGHT_];
//	
//	for(int i = 0; i < _WORLD_HEIGHT_; i++)
//	{
//		this->__world[i] = new Organism*[_WORLD_WIDTH_];
//	}
//	
//	for(int i = 0; i < _WORLD_HEIGHT_; i++)
//	{
//		for(int j = 0; j < _WORLD_WIDTH_; j++)
//		{
//			this->__world[i][j] = NULL;
//		}
//	}

	this->world = new Organism *[_WORLD_HEIGHT_][_WORLD_WIDTH_];
}

World::~World()
{
	
}

/*
Static
*/
Position World::getPosition(Organism& organism)
{
	Position pos = organism.getPosition();
	pos.setX(pos.getX() + 1);
	pos.setY(pos.getY() + 1);
	return pos;
}
