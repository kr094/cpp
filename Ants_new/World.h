#ifndef _WORLD_H_
#define _WORLD_H_
#include "Organism.h"

#define _WORLD_WIDTH_ 20
#define _WORLD_HEIGHT_ 20

class World
{
private:
	Organism **world[_WORLD_HEIGHT_][_WORLD_WIDTH_];
public:
	World();
	~World();
	
	static Position getPosition(Organism& organism);
};


#endif
