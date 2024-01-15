#include <fstream>
#include <sstream>

#include "player.h"



Player::Player() : Dentity()
{
	this->addSprite("assets/square.tga");
	this->sprite()->color = GREEN;
	this->scale += Point(-0.75, -0.75);
}

Player::~Player()
{

}

void Player::Mv(Vector2 vector) 
{
 this->position += vector;
}

void Player::update(float deltaTime)
{
	HandlePlayer(deltaTime);
	this->isInfected = false;
}

void Player::Movement(float deltaTime, int switchInt)
{
	switch (switchInt)
	{
	case 1:
		this->velocity.y = -1;
	break;

	case 2:
		this->velocity.y += 1;
	break;

	case 3:
		this->velocity.x += -1;
	break;
	
	case 4:
		this->velocity.x += 1;
	break;
	}
}

void Player::HandlePlayer(float deltaTime)
{
	this->velocity.normalize();
	this->velocity *= 250 * deltaTime;
	this->position += this->velocity;
	this->velocity *= 0;
}