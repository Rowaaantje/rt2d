// potion.cpp

#include "potion.h"

Potion::Potion() : Entity()
{
	this->addSprite("assets/square.tga");
	this->sprite()->color = YELLOW;
	this->scale += Point(-0.85, -0.85);
	this->position = Point2(SWIDTH / 2, SHEIGHT / 2);
}

Potion::~Potion()
{

}

void Potion::update(float deltaTime)
{
	
}

void Potion::RandomizePotion(float deltaTime)
{	
	// Generate random x and y coordinates within the screen bounds
	randomX = rand() % SWIDTH;
	randomY = rand() % SHEIGHT;

	// Set the potion's position
	this->position = Point2(randomX, randomY);

	// potion->position = Point2(SWIDTH / randomWidht, SHEIGHT / randomHeight);
}
