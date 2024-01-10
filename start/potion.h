// potion.h

#ifndef POTION_H
#define POTION_H

#include <entity.h>

class Potion: public Entity
{
public:
	Potion();
	virtual ~Potion();

private:
	/* add your private declarations */

	virtual void update(float deltaTime);
};

#endif /* POTION_H */
