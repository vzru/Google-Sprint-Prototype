#pragma once

#define WINDOW_SCREEN_WIDTH 640
#define WINDOW_SCREEN_HEIGHT 432
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FRAMES_PER_SECOND 60

#include "windows.h"
#include "Mesh.h"
#include "Timer.h"
#include "ShaderProgram.h"
#include "GameObject.h"
#include "Texture.h"
#include "Light.h"
#include <vector>

#include <GL\GL.h>
#include <GL\GLU.h>
#include <GL\glut.h>


class Game
{
public:
	Game();
	~Game();

	void initializeGame();
	void update();
	void draw();

	// Input callback functions
	void keyboardDown(unsigned char key, int mouseX, int mouseY);
	void keyboardUp(unsigned char key, int mouseX, int mouseY);
	void mouseClicked(int button, int state, int x, int y);
	void mouseMoved(int x, int y);

	Timer* updateTimer = nullptr;
	float totalGameTime = 0.0f;
	GameObject monkey1, monkey2, cube;

	ShaderProgram passThrough;
	ShaderProgram PhongNoTexture;
	ShaderProgram Phong;
	ShaderProgram PhongColorSides;
	std::vector<Light> pointLights;
	Light directionalLight;

	glm::mat4 cameraTransform;
	glm::mat4 cameraProjection;
	glm::mat4 lightSpinner;

	//Mesh monkey;
	//Mesh monkey2;
	//glm::mat4 monkeyTransform;
	//glm::mat4 monkeyRotate;
	//glm::mat4 monkeyTranslate;
	//float monkeyScale = 1.f;
	//glm::mat4 monkey2Transform;


private:
	bool shouldRotate = false;
	bool shouldLightsSpin = false;
	bool wKeydown = false;
	bool aKeydown = false;
	bool sKeydown = false;
	bool dKeydown = false;
	bool oKeydown = false;
	bool pKeydown = false;

};