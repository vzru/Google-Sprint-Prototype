#pragma once

#include <glm/glm.hpp>
#include "Mesh.h"
#include "ShaderProgram.h"
#include "Light.h"
#include <vector>
#include "Material.h"


class GameObject
{
public:

	GameObject();
	GameObject(const Mesh &m);
	~GameObject();

	Mesh mesh;
	glm::mat4 transform;

	glm::mat4 translate;
	glm::mat4 rotate;
	float scale = 1;

	Material mat;

	void loadMesh(const std::string &meshFile);
	void loadTexture(TextureType type, const std::string &texFile);


	void draw(ShaderProgram &shader, glm::mat4 &cameraTransform, glm::mat4 &cameraProjection, std::vector<Light> &pointLights,Light &directionalLight);
private:
};