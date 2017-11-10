
#pragma once
#include "GameObject.h"
#include "Level.h"

class Collision
{
public:
	Collision();
	~Collision();

	bool collided(GameObject &player, Face face);
	int collidedBottom(GameObject &player, std::vector<Face> faces);
	int collidedRight(GameObject &player, std::vector<Face> faces);
	int collidedTop(GameObject &player, std::vector<Face> faces);
	int collidedLeft(GameObject &player, std::vector<Face> faces);
private:
	int CollidedDirection; // 1 = top, 2 = right, 3 = bottom, 4 = left
	bool collideX;
	bool collideY;
	bool xDir;
	bool yDir;
	bool collideW = false;
	bool collideA = false;
	bool collideS = false;
	bool collideD = false;
};