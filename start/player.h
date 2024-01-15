// player.h

#ifndef PLAYER_H
#define PLAYER_H

#include <start/dentity.h>

// #include <rt2d/entity.h>



/// @brief The Player class is the Entity implementation.
class Player : public Dentity
{
public:
	/// @brief Constructor
	Player();
	/// @brief Destructor

	Vector2 velocity;
	virtual ~Player();
	void Mv(Vector2 vector);
	void Movement(float deltaTime, int switchInt);
	void HandlePlayer(float deltaTime);


	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:
	/* add your private declarations */
};

#endif /* PLAYER_H */
