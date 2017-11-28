
#pragma once
#include "GameObject.h"
#include "Level.h"

class Collision
{
public:
	Collision();
	~Collision();

	bool collided(GameObject &player, Face face);
	bool collided(GameObject & player, Face face, int dir);
	int colliding(GameObject & player, std::vector<Face> faces, Face* colObj = nullptr);
	int collidedBottom(GameObject &player, std::vector<Face> faces);
	int collidedRight(GameObject &player, std::vector<Face> faces);
	int collidedTop(GameObject &player, std::vector<Face> faces);
	int collidedLeft(GameObject &player, std::vector<Face> faces);
	static int CollidedDirection; // 1 = top, 2 = right, 3 = bottom, 4 = left
	static int CollidedDirection2; // 1 = top, 2 = right, 3 = bottom, 4 = left
	Face* collidedObject;
	bool alrdyCollided;
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