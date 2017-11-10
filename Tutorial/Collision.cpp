#include <iostream>
#include "Collision.h"
#include "glm\gtc\type_ptr.hpp"

Collision::Collision()
{
}

Collision::~Collision()
{

}

bool Collision::collided(GameObject &player, Face face)
{
	//double dArray[16] = { 0.0 };
	//const float *pSource = (const float*)glm::value_ptr(player.transform);
	//for (int i = 0; i < 16; ++i)
	//{
	//	dArray[i] = pSource[i];
	//	if (i % 4 == 3)
	//	{
	//		std::cout << dArray[i] << std::endl;
	//	}
	//	else
	//	{
	//		std::cout << dArray[i] << ' ';
	//	}
	//}
	//std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;

	glm::vec3 position(player.transform * glm::vec4(0.f, 0.f, 0.f, 1.f));
	//position.z = -position.z;

	//std::cout << position.x << " vs " << v1.x << " <> " << v2.x << ' ' << collideX << " / " << position.z << " vs " << v1.y << " <> " << v2.y << ' ' << collideY << " @ " << xDir << '/' << yDir << std::endl;

	//std::cout << position.x << '/' << position.z << std::endl;

	//if (!(position.x > v1.x && position.x < v2.x) && !(-position.z > v1.y && -position.z < v2.y))
	//{
	//	std::cout << "ZERO ZERO" << std::endl;
	//	collideX = false;
	//	collideY = false;
	//}

	glm::vec2 v1 = face.min;
	glm::vec2 v2 = face.max;
	glm::vec3 direction = position - glm::vec3((v1 + (v2 - v1)), 0.f);


	if ((position.x >= v1.x && position.x <= v2.x) && (position.z >= v1.y && position.z <= v2.y))
	{
		if (position.x > (v1.x + (v2.x - v1.x)) && position.z > (v1.y + (v2.y - v1.y)))
		{
			if ((position.x - (v1.x + (v2.x - v1.x)) - (v2.x - v1.x) / 2) < 0.3f)
				CollidedDirection = 1;
			
			if ((position.z - (v1.y + (v2.y - v1.y)) - (v2.y - v1.y) / 2) < 0.3f)
				CollidedDirection = 2;
		}
		else if (position.x > (v1.x + (v2.x - v1.x)) && position.z < (v1.y + (v2.y - v1.y)))
		{
			if ((direction.x - (v2.x - v1.x) / 2) < 0.3f)
				CollidedDirection = 2;

			if (((position.z - (v1.y + (v2.y - v1.y)) + (v2.y - v1.y) / 2) < 0.3f))
				CollidedDirection = 3;
		}
		else if (position.x < (v1.x + (v2.x - v1.x)) && position.z < (v1.y + (v2.y - v1.y)))
		{
			if ((direction.x + (v2.x - v1.x) / 2) < 0.3f)
				CollidedDirection = 4;

			if (((position.z - (v1.y + (v2.y - v1.y)) + (v2.y - v1.y) / 2) < 0.3f))
				CollidedDirection = 3;
		}
		else if (position.x < (v1.x + (v2.x - v1.x)) && position.z > (v1.y + (v2.y - v1.y)))
		{
			if ((direction.x + (v2.x - v1.x) / 2) < 0.3f)
				CollidedDirection = 4;

			if (((position.z - (v1.y + (v2.y - v1.y)) - (v2.y - v1.y) / 2) < 0.3f))
				CollidedDirection = 1;
		}
	//std::cout << "Collide Dir: " << CollidedDirection << std::endl;
		return true;
	}
	//if (position.z >= v1.y && position.z <= v2.y && (position.x - (v1.x + (v2.x - v1.x))) < 1.f)
	//{
	//	collideY = true;
	//	collideX = false;
	//	if (position.x < (v1.x + (v2.x - v1.x) / 2))
	//	{
	//		xDir = false;
	//	}
	//	else if (position.x > (v1.x + (v2.x - v1.x) / 2))
	//	{
	//		xDir = true;
	//	}
	//	if (position.x >= v1.x && position.x <= v2.x)
	//	{
	//		//std::cout << "Collided!" << std::endl;
	//		return true;
	//	}
	//}
	//if (position.x >= v1.x && position.x <= v2.x && (position.y - (v1.y + (v2.y - v1.y))) < 1.f)
	//{
	//	collideX = true;
	//	collideY = false;
	//	if (position.z < (v1.y + (v2.y - v1.y) / 2))
	//	{
	//		yDir = false;
	//	}
	//	else if (position.z > (v1.y + (v2.y - v1.y) / 2))
	//	{
	//		yDir = true;
	//	}
	//	if (position.z >= v1.y && position.z <= v2.y)
	//	{
	//		//std::cout << "Collided!" << std::endl;
	//		return true;
	//	}
	//}
	CollidedDirection = 0;
	return false;
}

int Collision::collidedBottom(GameObject & player, std::vector<Face> faces)
{
	for (auto& face : faces)
	{
		//std::cout << min[i].x << '/' << min[i].y << ' ' << max[i].x << '/' << max[i].y << std::endl;
		//bool collide = collided(player, face);
		//std::cout << i << '=' << yDir << std::endl;
		if (collided(player, face))
		{
			std::cout << "CollidedW!" << std::endl;
			return CollidedDirection;
		}
	}
	return 0;
}

int Collision::collidedRight(GameObject & player, std::vector<Face> faces)
{
	for (auto& face : faces)
	{
		//bool collide = collided(player, face);
		//std::cout << i << '=' << collideX << '-' << xDir << '/' << collideY << '-' << yDir << std::endl;
		if (collided(player, face))
		{
			std::cout << "CollidedA!" << std::endl;
			return CollidedDirection;
		}
	}
	return 0;
}

int Collision::collidedTop(GameObject & player, std::vector<Face> faces)
{
	for (auto& face : faces)
	{
		//bool collide = collided(player, face);
		//std::cout << i << '=' << yDir << std::endl;
		if (collided(player, face))
		{
			std::cout << "CollidedS!" << std::endl;
			return CollidedDirection;
		}
	}
	return 0;
}

int Collision::collidedLeft(GameObject & player, std::vector<Face> faces)
{
	for (auto& face : faces)
	{
		//bool collide = collided(player, face);
		//std::cout << i << '=' << collideX << '-' << xDir << '/' << collideY << '-' << yDir << std::endl;
		if (collided(player, face))
		{
			std::cout << "CollidedD!" << std::endl;
			return CollidedDirection;
		}
	}
	return 0;
}