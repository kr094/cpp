#include "Ant.h"

Ant::~Ant()
{
	
}

Ant::Ant()
{
	this->setPosition(Position(1, 1));
}

void Ant::move()
{
	this->setPosition(World::getPosition(*this));
}

