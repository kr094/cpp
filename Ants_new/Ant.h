#ifndef _ANT_H_
#define _ANT_H_
#include "Organism.h"
#include "World.h"
using namespace std;

class Ant : public Organism
{
public:	
	~Ant();
	Ant();
	
	void move();
};



#endif
