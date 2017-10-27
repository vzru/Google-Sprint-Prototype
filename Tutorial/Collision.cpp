#include <iostream>
#include "Collision.h"

Collision::Collision()
{
}

Collision::~Collision()
{

}

bool Collision::collided(GameObject player, glm::vec2 v1, glm::vec2 v2)
{
	if (glm::vec3(player.transform * glm::vec4(0.f, 0.f, 0.f, 1.f)).x >= v1.x && glm::vec3(player.transform * glm::vec4(0.f, 0.f, 0.f, 1.f)).x <= v2.x
		&& glm::vec3(player.transform * glm::vec4(0.f, 0.f, 0.f, 1.f)).y >= v1.y && glm::vec3(player.transform * glm::vec4(0.f, 0.f, 0.f, 1.f)).y <= v2.y)
	{
		std::cout << "Collided!" << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}
