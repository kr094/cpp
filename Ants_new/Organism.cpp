#include "Organism.h"

void Organism::setPosition(Position position)
{
	this->position = position;
}

Position Organism::getPosition()
{
	return this->position;
}

ostream& operator<<(ostream& out, Organism& organism)
{
	Position pos = organism.getPosition();
	return out << pos.getX() << ", " << pos.getY() << endl;
}
