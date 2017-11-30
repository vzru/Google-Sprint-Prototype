
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
	//int colliding(GameObject & player, std::vector<Face> faces, Face* colObj = nullptr);
	bool collideD(GameObject & player, Face face);
	bool colliding(GameObject & player, std::vector<Face> faces);
	bool collideD(glm::mat4 translate, Face face);
	bool colliding(glm::mat4 translate, std::vector<Face> faces);
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

};