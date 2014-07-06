#ifndef _ORGANISM_H_
#define _ORGANISM_H_
#include <iostream>
#include "Position.h"
using namespace std;

class Organism
{
private:
	Position position;
	char marker;	
	
public:
	virtual void move() = 0;
	
	void setPosition(Position position);
	Position getPosition();
	
	friend ostream& operator<<(ostream& out, Organism& organism);
	
};

#endif
