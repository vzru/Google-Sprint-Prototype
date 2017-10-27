
#pragma once
#include "GameObject.h"


class Collision
{
public:
	Collision();
	~Collision();

	bool collided(GameObject player, glm::vec2 v1, glm::vec2 v2);
	bool collideX;
	bool collideY;
	bool xDir;
	bool yDir;
private:

};