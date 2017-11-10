
#define _CRT_SECURE_NO_WARNINGS

#include "Level.h"

#include <fstream>
#include <iostream>
//#include "glm\glm.hpp"
using namespace std;

LevelHitBox::LevelHitBox(float r) : radius(r) {}
LevelHitBox::LevelHitBox() {}
LevelHitBox::~LevelHitBox() {}

bool LevelHitBox::loadFromFile(const std::string & file) {
	std::ifstream input;
	input.open(file);
	if (!input) {
		std::cout << "Level.loadFromFile: Could not open the file " << file << std::endl;
		return false;
	}

	std::string inputString;

	vector<glm::vec3> vertexData;
	
	// Index
	struct quad { unsigned int p[4]; };
	vector<quad> faceData;

	while (getline(input, inputString))
	{
		if (inputString[0] == '#')
		{
			cout << "Comment: " << inputString << endl;
			// this line is a comment so skip
			continue;
		}
		else if (inputString[0] == 'v')
		{
			if (inputString[1] == ' ')
			{
				// this is a vertex data
				glm::vec3 temp;

				sscanf(inputString.c_str(), "v %f %f %f", &temp.x, &temp.y, &temp.z);

				vertexData.push_back(temp);
			}
		}
		else if (inputString[0] == 'f')
		{
			// this is face data
			quad temp;

			sscanf(inputString.c_str(), "f %u %u %u %u",
				&temp.p[0], &temp.p[1], &temp.p[2], &temp.p[3]);

			faceData.push_back(temp);
		}
		else
		{
			cout << "Line not recognized, skipping: " << inputString << endl;
			continue;
		}
	}

	input.close();

	// unpack data

	for (auto& face : faceData)
	{
		Face temp;
		glm::vec3 vertex = vertexData[face.p[0] - 1];
		temp.min = { vertex.x - radius, vertex.z - radius };
		temp.max = { vertex.x + radius, vertex.z + radius };
		for (unsigned int j = 0; j < 4; j++)
		{
			vertex = vertexData[face.p[j] - 1];
			if (temp.min.x > vertex.x - radius && temp.min.y > vertex.z - radius) {
				temp.min.x = vertex.x - radius;
				temp.min.y = vertex.z - radius;
			}
			if (temp.max.x < vertex.x + radius && temp.max.y < vertex.z + radius) {
				temp.max.x = vertex.x + radius;
				temp.max.y = vertex.z + radius;
			}
		}
		temp.min.x += 2;
		temp.max.x += 2;
		cout << temp.min.x << "," << temp.min.y << " : " << temp.max.x << "," << temp.max.y << endl;
		hitBoxes.push_back(temp);
	}

	numFaces = faceData.size();
	numVertices = numFaces * 4;
	return true;
}