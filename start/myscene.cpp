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
	
	// create a single instance of MyEntity in the middle of the screen.
	// the Sprite is added in Constructor of MyEntity.
	player1 = new Player();
	player2 = new Player();
	enemy1 = new Enemy();
	potion = new Potion();

	player2->position = Point2(SWIDTH/2, SHEIGHT/2);
	player1->position = Point2(SWIDTH/2, SHEIGHT/2.2);

	enemy1->position = Point2(SWIDTH/1.5, SHEIGHT/2);
	potion->position = Point2(SWIDTH/1.7, SHEIGHT/2);

	// create the scene 'tree'
	// add myentity to this Scene as a child.
	this->addChild(player1);
	this->addChild(player2);
	this->addChild(enemy1);
	this->addChild(potion);

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

	// delete myentity from the heap (there was a 'new' in the constructor)
	delete player1;
	delete player2;
}

void MyScene::update(float deltaTime)
{
	quit();
	movement(deltaTime);
	drawLine();


if (enemy->isInfected || player2->isInfected)	
{
	if (infect(player1))
	{
		player1->sprite()->color = RED;
		player1->isInfected = true;
		std::cout << player1->isInfected << std::endl;
	}
}

if (enemy->isInfected || player1->isInfected )
{
	if (infect(player2))
	{
		player2->sprite()->color = RED;
		player2->isInfected = true;
		std::cout << player2->isInfected << std::endl;
	}
}

	if (pot(player1))
	{
		player1->sprite()->color = GREEN;
		player1->isInfected = false;
	}
	
	if (pot(player2))
	{
		player2->sprite()->color = GREEN;
		player2->isInfected = false;
	}

	// Forces(deltaTime);
	// Move(deltaTime);
	// player->position += Vector2(0.0f, g) * deltaTime;
	// player->position += Vector2(50.0f, 0.0f) * deltaTime;
}    

void MyScene::quit()
{
	if ( input()->getKey(KeyCode::Escape) )  {
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

void MyScene::forces(float deltaTime){ 

	Vector2 wind(150.0f, 0.0f);

	addForce(wind);
}

bool MyScene::infect(Player *player){


return (enemy->position.x  < player->position.x + player->sprite()->size.x * player->scale.x &&
		enemy->position.x + enemy1->sprite()->size.x * enemy->scale.x > player->position.x &&
		enemy->position.y < player->position.y + player->sprite()->size.y * player->scale.y &&
		enemy->position.y + enemy1->sprite()->size.y * enemy->scale.y > player->position.y);

}

bool MyScene::pot(Player *player){

return (potion->position.x  < player->position.x + player->sprite()->size.x * player->scale.x &&
		potion->position.x + potion->sprite()->size.x * potion->scale.x > player->position.x &&
		potion->position.y < player->position.y + player->sprite()->size.y * player->scale.y &&
		potion->position.y + potion->sprite()->size.y * potion->scale.y > player->position.y);
}

void MyScene::movement(float deltaTime)
{
	#ifndef Movement
	//W go up
	if ( input()->getKey(KeyCode::W) )  {
		player2->Movement(deltaTime, 1);
	}
	//S go down
	if ( input()->getKey(KeyCode::S) )  {
		// player->Mv(Vector2(0.0, velocity) * deltaTime);
		player2->Movement(deltaTime, 2);
	}
	//A go left
	if ( input()->getKey(KeyCode::A) )  {
		// player->Mv(Vector2(-velocity, 0.0) * deltaTime);
		player2->Movement(deltaTime, 3);
	}
	//D go right
	if ( input()->getKey(KeyCode::D) )  {
		// player->Mv(Vector2(velocity, 0.0) * deltaTime);
		player2->Movement(deltaTime, 4);
	}
	
	//crouch
	if ( input()->getKeyDown(KeyCode::LeftShift))  {
		player2->scale = Point(0.20, 0.20);
	}
	if ( input()->getKeyUp(KeyCode::LeftShift))  {
		player2->scale += Point(0.05, 0.05);

	}
	#endif /* Movement */

	#ifndef Movement1
	//W go up
	if ( input()->getKey(KeyCode::Up) )  {
		player1->Movement(deltaTime, 1);
	}
	//S go down
	if ( input()->getKey(KeyCode::Down) )  {
		// player->Mv(Vector2(0.0, velocity) * deltaTime);
		player1->Movement(deltaTime, 2);
	}
	//A go left
	if ( input()->getKey(KeyCode::Left) )  {
		// player->Mv(Vector2(-velocity, 0.0) * deltaTime);
		player1->Movement(deltaTime, 3);
	}
	//D go right
	if ( input()->getKey(KeyCode::Right) )  {		// player->Mv(Vector2(velocity, 0.0) * deltaTime);
		player1->Movement(deltaTime, 4);
	}
	
	//crouch
	if ( input()->getKeyDown(KeyCode::RightShift))  {
		player1->scale = Point(0.20, 0.20);
	}
	if ( input()->getKeyUp(KeyCode::RightShift))  {
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
	float mx = input()->getMouseX();
	float my = input()->getMouseY(); 
	//draw line
	ddLine(player1->position.x, player1->position.y, mx, my, BLUE); 
	// ddLine(enemy->position.x, enemy->position.y, mx, my, RED);
}