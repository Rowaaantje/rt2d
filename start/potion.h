// potion.h

#ifndef POTION_H
#define POTION_H

#include <entity.h>

class Potion: public Entity
{
public:
	Potion();
	virtual ~Potion();

	int randomX;
	int randomY;
	
	void RandomizePotion(float deltaTime);


private:
	/* add your private declarations */

	virtual void update(float deltaTime);
};

#endif /* POTION_H */
