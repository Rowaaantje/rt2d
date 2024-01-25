#include <fstream>
#include <sstream>

#include "enemy.h"

Enemy::Enemy(Player* p1, Player* p2) : Dentity()
{
	this->addSprite("assets/square.tga");
	this->sprite()->color = RED;
	this->scale += Point(-0.75, -0.75);
	this->isInfected = true;

	this->player1 = p1;
	this->player2 = p2;
}

Enemy::~Enemy()
{
	
}

void Enemy::update(float deltaTime)
{
	goMove(deltaTime);
	handleEnemy(deltaTime);
	RandomEnemyPos(deltaTime);
}

void Enemy::Mv(Vector2 vector) 
{
 this->position += vector;
}

void Enemy::goMove(float deltaTime)
{	
	float speed = 1;

	Vector2 p1pos = player1->position - this->position;
	Vector2 p2pos = player2->position - this->position;

	int closestPlayer;
	Vector2 direction;

	if (p1pos <= p2pos && !player1->isInfected) {
		closestPlayer = 1;
	} else if (!player2->isInfected) {
		closestPlayer = 2;
	}

	if (closestPlayer == 1) {
	direction = p1pos;
	} else {
	direction = p2pos;
	}
	
	this->position = this->position + direction * speed * deltaTime;
}

void Enemy::handleEnemy(float deltaTime)
{
	this->velocity.normalize();
	this->velocity *= 100 * deltaTime;
	this->position += this->velocity;
	this->velocity *= 0;
}

void Enemy::RandomEnemyPos(float deltaTime)
{
	if (this->position.x > SWIDTH + 10 || this->position.y > SHEIGHT + 10 || this->position.x < -10 || this->position.y < -10)
	{	
		switch (rand() % 3)
		{
		case 0:
			this->position = Vector2(rand() % SWIDTH, SHEIGHT + 10);
			break;
		case 1:
			this->position = Vector2(rand() % SWIDTH, -10);
			break;
		case 2:
			this->position = Vector2(SWIDTH + 10, rand() % SHEIGHT);
			break;
		case 3:
			this->position = Vector2(-10, rand() % SHEIGHT);
			break;
		}
	}
	
}

void Enemy::countDown(float countdownTime, float deltaTime)
{
    // starts timer
    if (time > 0)
    {
        time -= 1 * deltaTime;
    }
    else
    {
        // code
        std::cout << time << std::endl;

		this->removeChild(this);
		delete this;
        // resets timer
        time = countdownTime;
    }
}
