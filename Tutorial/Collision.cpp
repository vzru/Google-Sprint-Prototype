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

	//std::cout << position.x << " vs " << collidedObject.min.x << '/' << collidedObject.max.x << '-' << position.z << " vs " << collidedObject.min.y << '/' << collidedObject.max.y << std::endl;

	//if (!(position.x > v1.x && position.x < v2.x) && !(-position.z > v1.y && -position.z < v2.y))
	//{
	//	std::cout << "ZERO ZERO" << std::endl;
	//	collideX = false;
	//	collideY = false;
	//}

	glm::vec2 v1 = face.min;
	glm::vec2 v2 = face.max;
	float pCenterX = v1.x + (v2.x - v1.x) / 2;
	float pCenterY = v1.y + (v2.y - v1.y) / 2;
	glm::vec3 direction = position - glm::vec3(pCenterX, 0.f, pCenterY);
	//glColor3f(1.0f, 1.0f, 1.0f);
	//glBegin(GL_LINES);
	//glVertex3f(v1.x, -10.f, v1.y);
	//glVertex3f(v2.x, -10.f, v2.y);
	//glEnd();

	//std::cout << alrdyCollided << " Collide Dir: " << CollidedDirection << std::endl;

	if (!alrdyCollided)
	{
		if ((position.x >= v1.x && position.x <= v2.x) && (position.z >= v1.y && position.z <= v2.y))
		{
			std::cout << position.x << '/' << direction.x << " vs " << pCenterX << " / " << (v2.x - v1.x) / 2 << '@' << position.z << '/' << direction.z << " vs " << pCenterY << " / " << (v2.y - v1.y) / 2 << " | " << CollidedDirection << std::endl;
			if (position.x > pCenterX && position.z > pCenterY)
			{
				if (abs(direction.x - (v2.x - v1.x) / 2) < 0.2f)
					CollidedDirection = 2;

				if (abs(direction.z - (v2.y - v1.y) / 2) < 0.2f)
					CollidedDirection = 4;
			}
			else if (position.x > pCenterX && position.z < pCenterY)
			{
				if (abs(direction.x - (v2.x - v1.x) / 2) < 0.2f)
					CollidedDirection = 2;

				if (abs(direction.z + (v2.y - v1.y) / 2) < 0.2f)
					CollidedDirection = 1;
			}
			else if (position.x < pCenterX && position.z < pCenterY)
			{
				if (abs(direction.x + (v2.x - v1.x) / 2) < 0.2f)
					CollidedDirection = 3;

				if (abs(direction.z + (v2.y - v1.y) / 2) < 0.2f)
					CollidedDirection = 1;
			}
			else if (position.x < pCenterX && position.z > pCenterY)
			{
				if (abs(direction.x + (v2.x - v1.x) / 2) < 0.2f)
					CollidedDirection = 3;

				if (abs(direction.z - (v2.y - v1.y) / 2) < 0.2f)
					CollidedDirection = 4;
			}
			//std::cout << "Collide Dir: " << CollidedDirection << std::endl;
			collidedObject = face;
			alrdyCollided = true;
			return true;
		}
	}
	else if ((position.x < collidedObject.min.x || position.x > collidedObject.max.x) || (position.z < collidedObject.min.y || position.z > collidedObject.max.y))
	{
		//std::cout << "OUT!" << std::endl;
		alrdyCollided = false;
		CollidedDirection = 0;
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
	//CollidedDirection = 0;
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
			//std::cout << "CollidedW!" << std::endl;
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
			//std::cout << "CollidedA!" << std::endl;
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
			//std::cout << "CollidedS!" << std::endl;
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
			//std::cout << "CollidedD!" << std::endl;
			return CollidedDirection;
		}
	}
	return 0;
}