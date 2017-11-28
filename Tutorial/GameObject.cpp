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

void GameObject::loadTexture(TextureType type, const std::string &texFile)
{
	mat.loadTexture(type, texFile);
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

void GameObject::draw(ShaderProgram &shader, glm::mat4 &cameraTransform, glm::mat4 &cameraProjection, Light &directionalLight)//, std::vector<Light> &pointLights
{
	shader.bind();
	shader.sendUniformMat4("uModel", glm::value_ptr(transform), false);
	shader.sendUniformMat4("uView", glm::value_ptr(cameraTransform), false);
	shader.sendUniformMat4("uProj", glm::value_ptr(cameraProjection), false);

	//shader.sendUniform("uTex", 0);
	shader.sendUniform("material.diffuse", 0);
	shader.sendUniform("material.specular", 1);
	shader.sendUniform("material.normal", 2);
	shader.sendUniform("material.hue", mat.hue);
	shader.sendUniform("material.specularExponent", mat.specularExponent);

	//for (int i = 0; i < pointLights.size(); i++)
	//{
	//
	//	std::string prefix = "pointLights[" + std::to_string(i) + "].";
	//	shader.sendUniform(prefix + "position", cameraTransform * pointLights[i].positionDirection);
	//	shader.sendUniform(prefix + "ambient", pointLights[i].ambient);
	//	shader.sendUniform(prefix + "diffuse", pointLights[i].diffuse);
	//	shader.sendUniform(prefix + "specular", pointLights[i].specular);
	//	shader.sendUniform(prefix + "specularExponent", pointLights[i].specularExponent);
	//	shader.sendUniform(prefix + "constantAttenuation", pointLights[i].constantAttenuation);
	//	shader.sendUniform(prefix + "linearAttenuation", pointLights[i].linearAttenuation);
	//	shader.sendUniform(prefix + "quadraticAttenuation", pointLights[i].quadraticAttenuation);
	//
	//}
	//
	shader.sendUniform("directionalLight.direction", cameraTransform * directionalLight.positionDirection);
	shader.sendUniform("directionalLight.ambient", directionalLight.ambient);
	shader.sendUniform("directionalLight.diffuse", directionalLight.diffuse);
	shader.sendUniform("directionalLight.specular", directionalLight.specular);
	shader.sendUniform("directionalLight.specularExponent", directionalLight.specularExponent);

	//texture.bind();
	glActiveTexture(GL_TEXTURE0);
	mat.diffuse.bind();

	glActiveTexture(GL_TEXTURE1);
	mat.specular.bind();

	glActiveTexture(GL_TEXTURE2);
	mat.normal.bind();


	glBindVertexArray(mesh.vao);
	glDrawArrays(GL_TRIANGLES, 0, mesh.getNumVertices());
	glBindVertexArray(GL_NONE);

	mat.normal.unbind();

	glActiveTexture(GL_TEXTURE1);
	mat.specular.unbind();

	glActiveTexture(GL_TEXTURE0);
	mat.diffuse.unbind();

	shader.unbind();
}