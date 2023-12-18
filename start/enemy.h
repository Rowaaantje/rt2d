#ifndef ENEMY_H
#define ENEMY_H

#include <entity.h>

class Enemy: public Entity
{
public:
	Enemy();
	virtual ~Enemy();
	void Mv(Vector2 vector);

private:
	/* add your private declarations */

	virtual void update(float deltaTime);

};

#endif /* ENEMY_H */
