#ifndef MYSCENE_H
#define MYSCENE_H

#include <rt2d/scene.h>
#include "player.h"
#include "enemy.h"
#include "potion.h"

/// @brief The MyScene class is the Scene implementation.
class MyScene : public Scene
{
public:
	/// @brief Constructor
	MyScene();
	/// @brief Destructor
	virtual ~MyScene();

	int g = 10;
	int velocity = 0;
	int walk = 500;
	int sprint = 1000;


	Vector2 Velocity;//Point2
	Vector2 Acceleration;//Point2
	int mass; 

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);
	void addForce(Vector2 force);
	void move(float deltaTime);
	void quit();
	void forces(float deltaTime);
	void movement(float deltaTime);
	void drawLine();
	bool infect(Player *player);
	bool pot(Player *player);

private:
	/// @brief the rotating square in the middle of the screen
	Player* player1;
	Player* player2;
	
	Enemy* enemy1;
	Enemy* enemy;

	Potion* potion;
	/// @brief a Timer to rotate the color every n seconds
	
	// Timer t; kleur
};

#endif /* SCENE00_H */
