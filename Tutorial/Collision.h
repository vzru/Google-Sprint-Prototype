
#pragma once
#include "GameObject.h"
#include "Level.h"

class Collision
{
public:
	Collision();
	~Collision();

	bool collided(GameObject &player, Face face);
	bool collidedBottom(GameObject &player, std::vector<Face> faces);
	bool collidedRight(GameObject &player, std::vector<Face> faces);
	bool collidedTop(GameObject &player, std::vector<Face> faces);
	bool collidedLeft(GameObject &player, std::vector<Face> faces);
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