#ifndef ENEMY_H
#define ENEMY_H

#include <start/dentity.h>

#include "player.h"

class Enemy: public Dentity
{
public:
	Enemy(Player* p1, Player* p2); 
	virtual ~Enemy();
	
    float time;

	Vector2 velocity;
	void Mv(Vector2 vector);
	void handleEnemy(float deltaTime);
	void goMove(float deltaTime);
	void RandomEnemyPos(float deltaTime); 
	void countDown(float countdownTime, float deltaTime);

	

private:
	/* add your private declarations */
	virtual void update(float deltaTime);
	Player *player1;
	Player *player2;
};

#endif /* ENEMY_H */
