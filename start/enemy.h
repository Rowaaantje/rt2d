#ifndef ENEMY_H
#define ENEMY_H

#include <start/dentity.h>

class Enemy: public Dentity
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
