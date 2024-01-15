#include <fstream>
#include <sstream>

#include "enemy.h"

Enemy::Enemy() : Dentity()
{
	this->addSprite("assets/square.tga");
	this->sprite()->color = RED;
	this->scale += Point(-0.75, -0.75);
}

Enemy::~Enemy()
{

}

void Enemy::Mv(Vector2 vector) 
{
 this->position += vector;
}

void Enemy::update(float deltaTime)
{
	this->isInfected = true;
}

