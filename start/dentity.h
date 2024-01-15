// dentity.h

#ifndef DENTITY_H
#define DENTITY_H

#include <iostream>


#include <rt2d/entity.h>

class Dentity: public Entity
{
public:
	Dentity();
	virtual ~Dentity();

	bool isInfected;


    void update(float deltaTime);
	void Dentity::okay();

private:
	/* add your private declarations */
	
};

#endif /* DENTITY_H */
