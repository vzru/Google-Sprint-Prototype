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

	std::cout << position.x << " vs " << v1.x << " <> " << v2.x << ' ' << collideX << " / " << position.z << " vs " << v1.y << " <> " << v2.y << ' ' << collideY << " @ " << xDir << '/' << yDir << std::endl;
	
	if (position.x >= v1.x && position.x <= v2.x)
	{
		if (-(position.z) >= v1.y && -(position.z) <= v2.y)
		{
			std::cout << "Collided!" << std::endl;
			return true;
		}
		else
		{
			if (-(position.z) < v1.y)
			{
				yDir = false;
			}
			else if (-(position.z) > v2.y)
			{
				yDir = true;
			}
						
			collideX = true;
			collideY = false;
			return false;
		}
	}
	else if (-(position.z) >= v1.y && -(position.z) <= v2.y)
	{
		if (position.x >= v1.x && position.x <= v2.x)
		{
			std::cout << "Collided!" << std::endl;
			return true;
		}
		else
		{
			if (position.x < v1.x)
			{
				xDir = false;
			}
			else if (position.x > v2.x)
			{
				xDir = true;
			}
			collideY = true;
			collideX = false;
			return false;
		}
	}
	else
	{
		collideX = false;
		collideY = false;
		return false;
	}
}
