#include "GameObject.h"
#include <iostream>
#include <glm\gtc\type_ptr.hpp>

GameObject::GameObject()
{

}

GameObject::GameObject(const Mesh &m)
{
	mesh = m;
}

GameObject::~GameObject()
{
	//mesh.unload();
}

void GameObject::loadTexture(const std::string &texFile)
{
	if (!texture.load(texFile))
	{
		std::cout << "Texture failed to load." << std::endl;
		system("pause");
		exit(0);
	}
}

void GameObject::loadMesh(const std::string &meshFile)
{
	if (!mesh.loadFromFile(meshFile))
	{
		std::cout << "Model failed to load." << std::endl;
		system("pause");
		exit(0);
	}
}

void GameObject::draw(ShaderProgram &shader, glm::mat4 &cameraTransform, glm::mat4 &cameraProjection)
{
	shader.bind();
	shader.sendUniformMat4("uModel", glm::value_ptr(transform), false);
	shader.sendUniformMat4("uView", glm::value_ptr(cameraTransform), false);
	shader.sendUniformMat4("uProj", glm::value_ptr(cameraProjection), false);

	shader.sendUniform("uTex", 0);

	shader.sendUniform("lightPos", glm::vec4(0.f, 7.f, 5.f, 1.f));
	shader.sendUniform("objectColor", color);
	shader.sendUniform("lightAmbient", glm::vec3(0.15f, 0.15f, 0.15f));
	shader.sendUniform("lightDiffuse", glm::vec3(0.7f, 0.7f, 0.7f));
	shader.sendUniform("lightSpecular", glm::vec3(1.f, 1.f, 1.f));
	shader.sendUniform("lightSpecularExponent", 50.f);
	shader.sendUniform("attenuationConstant", 1.f);
	shader.sendUniform("attenuationLinear", 0.1f);
	shader.sendUniform("attenuationQuadratic", 0.01f);

	texture.bind();

	glBindVertexArray(mesh.vao);

	glDrawArrays(GL_TRIANGLES, 0, mesh.getNumVertices());

	glBindVertexArray(GL_NONE);

	texture.unbind();

	shader.unbind();
}

