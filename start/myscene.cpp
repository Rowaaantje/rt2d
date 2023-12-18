#include <fstream>
#include <sstream>

#include "myscene.h"
#include "player.h"
#include "enemy.h"

MyScene::MyScene() : Scene()
{
	// start the timer.
	// t.start(); kleur
	
	// create a single instance of MyEntity in the middle of the screen.
	// the Sprite is added in Constructor of MyEntity.
	player = new Player();
	enemy = new Enemy();
	player->position = Point2(SWIDTH/2, SHEIGHT/2);
	enemy->position = Point2(SWIDTH/1, SHEIGHT/2);

	// create the scene 'tree'
	// add myentity to this Scene as a child.
	this->addChild(player);
	this->addChild(enemy);

	Velocity;
	Acceleration;
	mass = 1;
	velocity = walk;
}

MyScene::~MyScene()
{
	// deconstruct and delete the Tree
	this->removeChild(player);

	// delete myentity from the heap (there was a 'new' in the constructor)
	delete player;
}

void MyScene::update(float deltaTime)
{
	if ( input()->getKey(KeyCode::Escape) )  {
		stop();
	}
	
	if (col())
	{
		player->sprite()->color = RED;
	}

	if ( input()->getKey(KeyCode::Tab) )  {
		player->sprite()->color = GREEN;
	}

	// else
	// {player->sprite()->color = BLUE;}
	// std::cout << "player scale" << player->scale << std::endl;

	#ifndef Movement
	//W go up
	if ( input()->getKey(KeyCode::W) )  {
		player->Mv(Vector2(0.0, -velocity) * deltaTime);
	}
	//S go down
	if ( input()->getKey(KeyCode::S) )  {
		player->Mv(Vector2(0.0, velocity) * deltaTime);
	}
	//A go left
	if ( input()->getKey(KeyCode::A) )  {
		player->Mv(Vector2(-velocity, 0.0) * deltaTime);
	}
	//D go right
	if ( input()->getKey(KeyCode::D) )  {
		player->Mv(Vector2(velocity, 0.0) * deltaTime);
	}
	
	//crouch
	if ( input()->getKeyDown(KeyCode::LeftShift))  {
		player->scale = Point(0.20, 0.20);
	}
	if ( input()->getKeyUp(KeyCode::LeftShift))  {
		player->scale += Point(0.05, 0.05);

	}
	#endif /* Movement */

	#ifndef EnemyMovement
	//W go up
	if ( input()->getKey(KeyCode::Up) )  {
		enemy->Mv(Vector2(0.0, -velocity) * deltaTime);
	}
	//S go down
	if ( input()->getKey(KeyCode::Down) )  {
		enemy->Mv(Vector2(0.0, velocity) * deltaTime);
	}
	//A go left
	if ( input()->getKey(KeyCode::Left) )  {
		enemy->Mv(Vector2(-velocity, 0.0) * deltaTime);
	}
	//D go right
	if ( input()->getKey(KeyCode::Right) )  {
		enemy->Mv(Vector2(velocity, 0.0) * deltaTime);
	}
	
	//crouch
	if ( input()->getKeyDown(KeyCode::RightShift))  {
		enemy->scale = Point(0.20, 0.20);
	}
	if ( input()->getKeyUp(KeyCode::RightShift))  {
		enemy->scale += Point(0.05, 0.05);
	}
	#endif /* Enemy Movement */

	//clear pervouis drawline
	ddClear();
	float mx = input()->getMouseX();
	float my = input()->getMouseY(); 
	//draw line
	ddLine(player->position.x, player->position.y, mx, my, BLUE); 
	ddLine(enemy->position.x, enemy->position.y, mx, my, RED); 
	
	// Forces(deltaTime);
	// Move(deltaTime);
	// player->position += Vector2(0.0f, g) * deltaTime;
	// player->position += Vector2(50.0f, 0.0f) * deltaTime;
}    

void MyScene::Move(float deltaTime)
{
	Velocity += Acceleration * deltaTime;
	this->position += Velocity * deltaTime;
	// Reset acceleration
	Acceleration *= 0.0f;
}

void MyScene::AddForce(Vector2 force)
{
	this->Acceleration += force / mass;
}

void MyScene::Forces(float deltaTime){ 

	Vector2 wind(150.0f, 0.0f);

	AddForce(wind);

}

bool MyScene::col(){

return (enemy->position.x  < player->position.x + player->sprite()->size.x * player->scale.x &&
		enemy->position.x + enemy->sprite()->size.x * enemy->scale.x > player->position.x &&
		enemy->position.y < player->position.y + player->sprite()->size.y * player->scale.y &&
		enemy->position.y + enemy->sprite()->size.y * enemy->scale.y > player->position.y);
}
