#pragma once
#include "Mesh.h"
#include "GameObject.h"
#include <vector>
#include "glm/vec3.hpp"

class LevelMesh : public Mesh {
public:
	LevelMesh();
	~LevelMesh();

	// Load a mesh and send it to OpenGL and calculate the hitboxes
	bool loadFromFile(const std::string &file);
private:
	std::vector<glm::vec2> ceiling;
};

class Level : GameObject {
public:
	Level();
	~Level();

	void update(float dt);
	virtual void draw(ShaderProgram &shader, glm::mat4 &cameraTransform, glm::mat4 &cameraProjection);
};

struct Face {
	glm::vec2 min, max;
};

class LevelHitBox : public Mesh {
public:
	LevelHitBox();
	~LevelHitBox();

	// Load a mesh of hitboxes
	bool loadFromFile(const std::string &file);
private:
	std::vector<Face> hitBoxes;
};