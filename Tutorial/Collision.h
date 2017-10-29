
#pragma once
#include "GameObject.h"


class Collision
{
public:
	Collision();
	~Collision();

	bool collided(GameObject player, glm::vec2 v1, glm::vec2 v2);
	
	bool collidedBottom(GameObject &player, glm::vec2 *min, glm::vec2 *max);
	bool collidedRight(GameObject &player, glm::vec2 *min, glm::vec2 *max);
	bool collidedTop(GameObject &player, glm::vec2 *min, glm::vec2 *max);
	bool collidedLeft(GameObject &player, glm::vec2 *min, glm::vec2 *max);
private:
	bool collideX;
	bool collideY;
	bool xDir;
	bool yDir;
	bool collideW = false;
	bool collideA = false;
	bool collideS = false;
	bool collideD = false;
};