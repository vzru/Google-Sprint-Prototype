
#define _CRT_SECURE_NO_WARNINGS

#include "Level.h"

#include <fstream>
#include <iostream>
//#include "glm\glm.hpp"
using namespace std;

struct MeshFace
{
	MeshFace()
	{
		vertices[0] = 0;
		vertices[1] = 0;
		vertices[2] = 0;

		textureUVs[0] = 0;
		textureUVs[1] = 0;
		textureUVs[2] = 0;

		normals[0] = 0;
		normals[1] = 0;
		normals[2] = 0;
	}

	MeshFace(unsigned int v1, unsigned int v2, unsigned int v3,
		unsigned int t1, unsigned int t2, unsigned int t3,
		unsigned int n1, unsigned int n2, unsigned int n3)
	{
		vertices[0] = v1;
		vertices[1] = v2;
		vertices[2] = v3;

		textureUVs[0] = t1;
		textureUVs[1] = t2;
		textureUVs[2] = t3;

		normals[0] = n1;
		normals[1] = n2;
		normals[2] = n3;
	}

	unsigned int vertices[3];
	unsigned int textureUVs[3];
	unsigned int normals[3];
};

LevelMesh::LevelMesh() {}
LevelMesh::~LevelMesh() {}

bool LevelMesh::loadFromFile(const std::string & file) {
	std::ifstream input;
	input.open(file);
	if (!input)
	{
		std::cout << "Mesh.loadFromFile: Could not open the file " << file << std::endl;
		return false;
	}

	std::string inputString;

	vector<glm::vec3> vertexData;
	vector<glm::vec2> textureData;
	vector<glm::vec3> normalData;

	// Index
	vector<MeshFace> faceData;

	// OpenGL ready data
	vector<float> unpackedVertexData;
	vector<float> unpackedTextureData;
	vector<float> unpackedNormalData;

		while (getline(input, inputString))
		{
			if (inputString[0] == '#')
			{
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
				else if (inputString[1] == 't')
				{
					// this is UV data
					glm::vec2 temp;

					sscanf(inputString.c_str(), "vt %f %f", &temp.x, &temp.y);

					textureData.push_back(temp);

				}
				else if (inputString[1] == 'n')
				{
					// this is normal data
					glm::vec3 temp;

					sscanf(inputString.c_str(), "vn %f %f %f", &temp.x, &temp.y, &temp.z);

					normalData.push_back(temp);

				}
			}
			else if (inputString[0] == 'f')
			{
				// this is face data
				MeshFace temp;

				sscanf(inputString.c_str(), "f %u/%u/%u %u/%u/%u %u/%u/%u",
					&temp.vertices[0], &temp.textureUVs[0], &temp.normals[0],
					&temp.vertices[1], &temp.textureUVs[1], &temp.normals[1],
					&temp.vertices[2], &temp.textureUVs[2], &temp.normals[2]);

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

		for (unsigned int i = 0; i < faceData.size(); i++)
		{
			for (unsigned int j = 0; j < 3; j++)
			{
				unpackedVertexData.push_back(vertexData[faceData[i].vertices[j] - 1].x);
				unpackedVertexData.push_back(vertexData[faceData[i].vertices[j] - 1].y);
				unpackedVertexData.push_back(vertexData[faceData[i].vertices[j] - 1].z);

				unpackedTextureData.push_back(textureData[faceData[i].textureUVs[j] - 1].x);
				unpackedTextureData.push_back(textureData[faceData[i].textureUVs[j] - 1].y);

				unpackedNormalData.push_back(normalData[faceData[i].normals[j] - 1].x);
				unpackedNormalData.push_back(normalData[faceData[i].normals[j] - 1].y);
				unpackedNormalData.push_back(normalData[faceData[i].normals[j] - 1].z);

			}
		}

		numFaces = faceData.size();
		numVertices = numFaces * 3;

	// Send data to OpenGL
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vboVertices);
	glGenBuffers(1, &vboUVs);
	glGenBuffers(1, &vboNormals);

	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);	// Vertices
	glEnableVertexAttribArray(1);	// UVs
	glEnableVertexAttribArray(2);	// Normals
	
	// Vertices
	glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unpackedVertexData.size(), &unpackedVertexData[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, vboUVs);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unpackedTextureData.size(), &unpackedTextureData[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * unpackedNormalData.size(), &unpackedNormalData[0], GL_STATIC_DRAW);
	glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, BUFFER_OFFSET(0));

	glBindBuffer(GL_ARRAY_BUFFER, GL_NONE);
	glBindVertexArray(GL_NONE);

	float high = 0.0f;
	for (auto vert : vertexData)
		if (vert.y < high)
			high = vert.y;
	for (auto vert : vertexData)
		if (vert.y == high)
			ceiling.push_back({ vert.x, vert.z });
	return true;
}


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
		for (unsigned int j = 0; j < 4; j++)
		{
			glm::vec3 vertex = vertexData[face.p[j] - 1];
			if (temp.min.x > vertex.x && temp.min.y > vertex.z) {
				temp.min.x = vertex.x - radius;
				temp.min.y = vertex.z - radius;
			}
			if (temp.max.x < vertex.x && temp.max.y < vertex.z) {
				temp.max.x = vertex.x + radius;
				temp.max.y = vertex.z + radius;
			}
		}
		hitBoxes.push_back(temp);
	}

	numFaces = faceData.size();
	numVertices = numFaces * 4;
}