#include <iostream>
#include "Collision.h"
#include "glm\gtc\type_ptr.hpp"

Collision::Collision()
{
}

Collision::~Collision()
{

}

bool Collision::collided(GameObject player, glm::vec2 v1, glm::vec2 v2)
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

	//std::cout << position.x << " vs " << v1.x << " <> " << v2.x << ' ' << collideX << " / " << position.z << " vs " << v1.y << " <> " << v2.y << ' ' << collideY << " @ " << xDir << '/' << yDir << std::endl;

	//std::cout << position.x << '/' << -(position.z) << std::endl;

	//if (!(position.x > v1.x && position.x < v2.x) && !(-position.z > v1.y && -position.z < v2.y))
	//{
	//	std::cout << "ZERO ZERO" << std::endl;
	//	collideX = false;
	//	collideY = false;
	//}

	if ((position.x >= v1.x && position.x <= v2.x) && (-position.z >= v1.y && -position.z <= v2.y))
	{
		return true;
	}
	if (-position.z >= v1.y && -position.z <= v2.y)
	{
		collideY = true;
		collideX = false;
		if (position.x < (v1.x + (v2.x - v1.x) / 2))
		{
			xDir = false;
		}
		else if (position.x > (v1.x + (v2.x - v1.x) / 2))
		{
			xDir = true;
		}
		if (position.x >= v1.x && position.x <= v2.x)
		{
			//std::cout << "Collided!" << std::endl;
			return true;
		}
	}
	if (position.x >= v1.x && position.x <= v2.x)
	{
		collideX = true;
		collideY = false;
		if (-position.z < (v1.y + (v2.y - v1.y) / 2))
		{
			yDir = false;
		}
		else if (-position.z > (v1.y + (v2.y - v1.y) / 2))
		{
			yDir = true;
		}
		if (-(position.z) >= v1.y && -(position.z) <= v2.y)
		{
			//std::cout << "Collided!" << std::endl;
			return true;
		}
	}
	return false;
}

bool Collision::collidedBottom(GameObject & player, glm::vec2 * min, glm::vec2 * max)
{
	for (int i = 0; i < 2; i++)
	{
		//std::cout << min[i].x << '/' << min[i].y << ' ' << max[i].x << '/' << max[i].y << std::endl;
		bool collide = collided(player, min[i], max[i]);
		//std::cout << i << '=' << yDir << std::endl;
		if (!collide || collideY || collideX && yDir)
		{
			collideW = false;
		}
		else
		{
			std::cout << "CollidedW!" << std::endl;
			return true;
		}
	}
	return collideW;
}

bool Collision::collidedRight(GameObject & player, glm::vec2 * min, glm::vec2 * max)
{
	for (int i = 0; i < 2; i++)
	{
		bool collide = collided(player, min[i], max[i]);
		//std::cout << i << '=' << collideX << '-' << xDir << '/' << collideY << '-' << yDir << std::endl;
		if (!collide || collideX || collideY && !xDir)
		{
			collideA = false;
		}
		else
		{
			std::cout << "CollidedA!" << std::endl;
			return true;
		}
	}
	return collideA;
}

bool Collision::collidedTop(GameObject & player, glm::vec2 * min, glm::vec2 * max)
{
	for (int i = 0; i < 2; i++)
	{
		bool collide = collided(player, min[i], max[i]);
		//std::cout << i << '=' << yDir << std::endl;
		if (!collide || collideY || collideX && !yDir)
		{
			collideS = false;
		}
		else
		{
			std::cout << "CollidedS!" << std::endl;
			return true;
		}
	}
	return collideS;
}

bool Collision::collidedLeft(GameObject & player, glm::vec2 * min, glm::vec2 * max)
{
	for (int i = 0; i < 2; i++)
	{
		bool collide = collided(player, min[i], max[i]);
		//std::cout << i << '=' << collideX << '-' << xDir << '/' << collideY << '-' << yDir << std::endl;
		if (!collide || collideX || collideY && xDir)
		{
			collideD = false;
		}
		else
		{
			std::cout << "CollidedD!" << std::endl;
			return true;
		}
	}
	return collideD;
}