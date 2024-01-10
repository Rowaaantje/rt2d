// potion.cpp

#include "potion.h"

Potion::Potion() : Entity()
{
	this->addSprite("assets/square.tga");
	this->sprite()->color = YELLOW;
	this->scale += Point(-0.85, -0.85);
}

Potion::~Potion()
{

}


void Potion::update(float deltaTime)
{
	
}
