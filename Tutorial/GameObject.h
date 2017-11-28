#pragma once

#include <glm/glm.hpp>
#include "Mesh.h"
#include "ShaderProgram.h"
#include <vector>
#include "Material.h"
#include "Light.h"


class GameObject
{
public:

	GameObject();
	GameObject(const Mesh &m);
	~GameObject();

	Mesh mesh;
	Texture texture;
	glm::mat4 transform;
	glm::vec4 color;

	glm::mat4 translate;
	glm::mat4 rotate;
	float scale = 1;
	float cd;
	float hp;
	bool hit;

	Material mat;

	void loadMesh(const std::string &meshFile);
	void loadTexture(TextureType type, const std::string &texFile);


	void draw(ShaderProgram &shader, glm::mat4 &cameraTransform, glm::mat4 &cameraProjection, Light &directionalLight);
private:
};