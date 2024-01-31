#include <fstream>
#include <sstream>

#include "myscene.h"
#include "player.h"
#include "enemy.h"
#include "potion.h"

MyScene::MyScene() : Scene()
{
	// start the timer.
	// t.start(); kleur
	player1 = new Player();
	player2 = new Player();
	potion = new Potion();
	// enemy = new Enemy(player1, player2);

	player1->position = Point2(SWIDTH / 2.2, SHEIGHT / 2.2);
	player2->position = Point2(SWIDTH / 1.8, SHEIGHT / 2.2);

	player1Cam = new Camera();

	// create the scene 'tree'
	this->addChild(player1);
	this->addChild(player2);
	this->addChild(potion);


	for (size_t i = 0; i < 4; i++)
	{
		enemies.push_back(new Enemy(player1, player2));
		this->addChild(enemies[i]);
	}
	
	
	Velocity;
	Acceleration;
	mass = 1;
	velocity = walk;
}

MyScene::~MyScene()
{
	// deconstruct and delete the Tree
	this->removeChild(player1);
	this->removeChild(player2);
	this->removeChild(potion);

	delete player1;
	delete player2;
	delete player1Cam;
	
	// delete enemies;
	for (size_t i = 0; i < enemies.size(); i++)
	{
		this->removeChild(enemies[i]);
		delete enemies[i];
	}
}

void MyScene::update(float deltaTime)
{
	quit();
	hell();
	movement(deltaTime);
	CamPlayer(deltaTime);

	// drawLine();

	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->isInfected)
		{
			//player1 = infected"
			if (collision(enemies[i], player1))
			{
				player1->sprite()->color = RED;
				player1->isInfected = true;
			}

			//player2 = infected
			if (collision(enemies[i], player2))
			{
				player2->sprite()->color = RED;
				player2->isInfected = true;
			}
		}
	}
	
	if (player1->isInfected || player2->isInfected)
	{
		if (collision(player1, player2))
		{
			player1->sprite()->color = RED;
			player1->isInfected = true;

			player2->sprite()->color = RED;
			player2->isInfected = true;
		}
	}

	if (collision(potion, player1))
	{
		player1->sprite()->color = GREEN;
		player1->isInfected = false;
		std::cout << "player1 = human" << std::endl;
		potion->RandomizePotion(deltaTime);
	}

	if (collision(potion, player2))
	{
		player2->sprite()->color = GREEN;
		player2->isInfected = false;
		std::cout << "player2 = human" << std::endl;
		potion->RandomizePotion(deltaTime);
	}
	// Forces(deltaTime);
	// Move(deltaTime);
	// player->position += Vector2(0.0f, g) * deltaTime;
	// player->position += Vector2(50.0f, 0.0f) * deltaTime;
}

void MyScene::quit()
{
	if (input()->getKey(KeyCode::Escape))
	{
		stop();
	}
}

void MyScene::move(float deltaTime)
{
	Velocity += Acceleration * deltaTime;
	this->position += Velocity * deltaTime;
	// Reset acceleration
	Acceleration *= 0.0f;
}

void MyScene::addForce(Vector2 force)
{
	this->Acceleration += force / mass;
}

void MyScene::forces(float deltaTime)
{

	Vector2 wind(150.0f, 0.0f);
	addForce(wind);
}

bool MyScene::collision(Entity *playerA, Entity *playerB)
{
	return (playerA->position.x < playerB->position.x + playerB->sprite()->size.x * playerB->scale.x &&
			playerA->position.x + playerA->sprite()->size.x * playerA->scale.x > playerB->position.x &&
			playerA->position.y < playerB->position.y + playerB->sprite()->size.y * playerB->scale.y &&
			playerA->position.y + playerA->sprite()->size.y * playerA->scale.y > playerB->position.y);
}

void MyScene::movement(float deltaTime)
{
#ifndef Movement
	// W go up
	if (input()->getKey(KeyCode::W))
	{
		player2->Movement(deltaTime, 1);
	}
	// S go down
	if (input()->getKey(KeyCode::S))
	{
		// player->Mv(Vector2(0.0, velocity) * deltaTime);
		player2->Movement(deltaTime, 2);
	}
	// A go left
	if (input()->getKey(KeyCode::A))
	{
		// player->Mv(Vector2(-velocity, 0.0) * deltaTime);
		player2->Movement(deltaTime, 3);
	}
	// D go right
	if (input()->getKey(KeyCode::D))
	{
		// player->Mv(Vector2(velocity, 0.0) * deltaTime);
		player2->Movement(deltaTime, 4);
	}

	// crouch
	if (input()->getKeyDown(KeyCode::LeftShift))
	{
		player2->scale = Point(0.20, 0.20);
	}
	if (input()->getKeyUp(KeyCode::LeftShift))
	{
		player2->scale += Point(0.05, 0.05);
	}
#endif /* Movement */

#ifndef Movement1
	// W go up
	if (input()->getKey(KeyCode::Up))
	{
		player1->Movement(deltaTime, 1);
	}
	// S go down
	if (input()->getKey(KeyCode::Down))
	{
		// player->Mv(Vector2(0.0, velocity) * deltaTime);
		player1->Movement(deltaTime, 2);
	}
	// A go left
	if (input()->getKey(KeyCode::Left))
	{
		// player->Mv(Vector2(-velocity, 0.0) * deltaTime);
		player1->Movement(deltaTime, 3);
	}
	// D go right
	if (input()->getKey(KeyCode::Right))
	{ // player->Mv(Vector2(velocity, 0.0) * deltaTime);
		player1->Movement(deltaTime, 4);
	}

	// crouch
	if (input()->getKeyDown(KeyCode::RightShift))
	{
		player1->scale = Point(0.20, 0.20);
	}
	if (input()->getKeyUp(KeyCode::RightShift))
	{
		player1->scale += Point(0.05, 0.05);
	}
#endif /* Movement1 */

	// #ifndef EnemyMovement
	// //W go up
	// if ( input()->getKey(KeyCode::Up) )  {
	// 	enemy->Mv(Vector2(0.0, -velocity) * deltaTime);
	// }
	// //S go down
	// if ( input()->getKey(KeyCode::Down) )  {
	// 	enemy->Mv(Vector2(0.0, velocity) * deltaTime);
	// }
	// //A go left
	// if ( input()->getKey(KeyCode::Left) )  {
	// 	enemy->Mv(Vector2(-velocity, 0.0) * deltaTime);
	// }
	// //D go right
	// if ( input()->getKey(KeyCode::Right) )  {
	// 	enemy->Mv(Vector2(velocity, 0.0) * deltaTime);
	// }

	// //crouch
	// if ( input()->getKeyDown(KeyCode::RightShift))  {
	// 	enemy->scale = Point(0.20, 0.20);
	// }
	// if ( input()->getKeyUp(KeyCode::RightShift))  {
	// 	enemy->scale += Point(0.05, 0.05);
	// }
	// #endif /* Enemy Movement */
}

void MyScene::drawLine()
{
	ddClear();
	float x = input()->getMouseX();
	float y = input()->getMouseY();
	// draw line
	ddLine(player1->position.x, player1->position.y, x, y, BLUE);
	// ddLine(enemy->position.x, enemy->position.y, mx, my, RED);
}

void MyScene::hell()
{
	bool yes = false;
	if(input()->getKey(KeyCode::Alpha1))
	{
		for (size_t i = 0; i < spawnCount; i++)
		{
			enemies.push_back(new Enemy(player1, player2));
			this->addChild(enemies[i]);
			// enemies[i]->position = Vector2(rand() % SWIDTH, rand() % SHEIGHT);
			yes = true;
		}
		spawnCount++; // increment the spawn count each time enemies are spawned
		std::cout << spawnCount << std::endl;
	}

	if(input()->getKeyDown(KeyCode::Alpha2))
	{
		for (size_t i = 0; i < spawnCount; i++)
		{
			enemies.push_back(new Enemy(player1, player2));
			this->addChild(enemies[i]);
			// enemies[i]->position = Vector2(rand() % SWIDTH, rand() % SHEIGHT);
			yes = true;
		}
		spawnCount++; // increment the spawn count each time enemies are spawned
		std::cout << spawnCount << std::endl;
	}
	
	
}

void MyScene::CamPlayer(float deltaTime) //camera follow the player 
{
	player1Cam->position =  _p1Pos;

	_p1Pos = player1->position;

	// if(_p1Pos)

	std::cout << _p1Pos << std::endl;
}
