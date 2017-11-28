#pragma once

#define WINDOW_SCREEN_WIDTH 640
#define WINDOW_SCREEN_HEIGHT 432
#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 1000
#define FRAMES_PER_SECOND 60
#define PLAYER_RADIUS 0.5f

#include "windows.h"
#include "Mesh.h"
#include "Timer.h"
#include "ShaderProgram.h"
#include "GameObject.h"
#include "Texture.h"
#include "Light.h"
#include <vector>
#include "Collision.h"
#include "Level.h"

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
	void mousePassive(int x, int y);

	bool clearLevel(glm::vec4 goal);

	void Death();

	Timer* updateTimer = nullptr;
	float totalGameTime = 0.0f;
	GameObject player, level, hitboxes, enemyLoadIn, bullet;
	LevelHitBox levelHitBox;

	Collision collision;
	Collision collision2;
	bool shooting = false;
	//Face collidedObject;
	std::vector<GameObject*> enemies;
	std::vector<GameObject*> bullets;

	//ShaderProgram passThrough;
	//ShaderProgram PhongNoTexture;
	ShaderProgram Phong;
	Light directionalLight;

	glm::mat4 cameraTransform;
	glm::mat4 cameraProjection;
	glm::vec3 playerPos, enemyPos;
	glm::vec4 exitGoal = glm::vec4(93.f, 96.f, 49.5f, 52.5f);

	//Mesh monkey;
	//Mesh level;
	//glm::mat4 monkeyTransform;
	//glm::mat4 monkeyRotate;
	//glm::mat4 monkeyTranslate;
	//float monkeyScale = 1.f;
	//glm::mat4 monkey2Transform;


private:
	bool shouldRotate = false;
	bool wKeydown = false;
	bool aKeydown = false;
	bool sKeydown = false;
	bool dKeydown = false;
	bool oKeydown = false;
	bool pKeydown = false;

};