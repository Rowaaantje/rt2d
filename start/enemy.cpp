#include <fstream>
#include <sstream>

#include "enemy.h"
#include "myscene.h"

Enemy::Enemy(Player *p1, Player *p2) : Dentity()
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
	scaleEnemy(deltaTime);
}

void Enemy::Mv(Vector2 vector)
{
	this->position += vector;
}
// move to te closest player
void Enemy::goMove(float deltaTime)
{
	float speed = 175;

	Vector2 p1pos = player1->position - this->position;
	Vector2 p2pos = player2->position - this->position;

	int closestPlayer;
	Vector2 direction;

	if (p1pos <= p2pos && !player1->isInfected)
	{
		closestPlayer = 1;
	}
	else if (!player2->isInfected)
	{
		closestPlayer = 2;
	}

	if (closestPlayer == 1)
	{
		p1pos.normalize();
		direction = p1pos;
	}
	else
	{
		p2pos.normalize();
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

void Enemy::walkAnim(float deltaTime)
{

	// switch (i)
	// {
	// case true:
	// 	sTime += 1 * deltaTime;
	// 	this->scale -= 0.5 * deltaTime;
	// 	if (sTime >= 0.5)
	// 	{
	// 		i = false;
	// 		sTime = 0;
	// 	}
	// 	break;

	// case false:
	// 	sTime += 0.05 * deltaTime;
	// 	this->scale += 0.5 * deltaTime;
	// 	if (sTime >= 0.5)
	// 	{
	// 		i = true;
	// 		sTime = 0;
	// 	}
	// 	break;
	// }
}

void Enemy::RandomEnemyPos(float deltaTime)
{
	countdownTime = rand() % 4 + 1;

	if (time > 0)
	{
		time -= 1 * deltaTime;
	}
	else
	{
		// randomly respawn
		switch (rand() % 5)
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
		case 4:
			this->position = Vector2(-10, rand() % SHEIGHT);
			break;
		}

		// if the player is outside the screen respawn
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
		time = countdownTime;
		// std::cout << countdownTime << std::endl;
	}
}

void Enemy::scaleEnemy(float deltaTime)
{
	if(input()->getKey(KeyCode::Q))
	{
		this->scale += 1 * deltaTime;
	}
	
	if(input()->getKey(KeyCode::E))
	{
		this->scale -= 1 * deltaTime;
	}
}
