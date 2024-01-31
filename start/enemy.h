#ifndef ENEMY_H
#define ENEMY_H

#include <start/dentity.h>

#include "player.h"


class Enemy: public Dentity
{
public:
	Enemy(Player* p1, Player* p2); 
	virtual ~Enemy();

	float sTime;
    float time;
	Vector2 velocity;
	void Mv(Vector2 vector);
	void handleEnemy(float deltaTime);	
	void goMove(float deltaTime);
	void walkAnim(float deltaTime);

	float countdownTime;
	void RandomEnemyPos(float deltaTime);

	void scaleEnemy(float deltaTime);
	
private:
	/* add your private declarations */
	virtual void update(float deltaTime);
	Player *player1;
	Player *player2;
	bool i;

};

#endif /* ENEMY_H */
