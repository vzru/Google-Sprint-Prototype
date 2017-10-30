#pragma once
#include "Mesh.h"
#include "GameObject.h"
#include <vector>

struct Face {
	glm::vec2 min, max;
};

class LevelHitBox : public Mesh {
public:
	LevelHitBox(float r);
	LevelHitBox();
	~LevelHitBox();

	// Load a mesh of hitboxes
	bool loadFromFile(const std::string &file);
	std::vector<Face> hitBoxes;
private:
	float radius;
};