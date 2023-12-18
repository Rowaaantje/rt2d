#include <fstream>
#include <sstream>

#include "player.h"


Player::Player() : Entity()
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
	// ###############################################################
	// Rotate
	// ###############################################################
	// this->rotation.z += HALF_PI * deltaTime; // 90 deg/sec
	// if (this->rotation.z > TWO_PI) {
	// 	this->rotation.z -= TWO_PI;
	// }
}


