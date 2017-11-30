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

	enum state
	{
		MENU,
		GAME,
		DEATH,
		WIN,
		QUIT
	};

	void initializeGame();
	void update();
	void draw();

	// Input callback functions
	void keyboardDown(unsigned char key, int mouseX, int mouseY);
	void keyboardUp(unsigned char key, int mouseX, int mouseY);
	void windowReshape(int width, int height);
	void mouseClicked(int button, int state, int x, int y);
	void mousePassive(int x, int y);

	bool clearLevel(glm::vec4 goal);

	void InitializeEnemy();

	void Death();

	void Win();

	Timer* updateTimer = nullptr;
	float totalGameTime = 0.0f;
	GameObject player, level, hitboxes, bullet, screen, win, death, hud, hpbar, playB, quitB;
	GameObject enemyLoadIn, enemy1, enemy2;
	LevelHitBox levelHitBox;
	Collision collision;
	Collision collision2;
	state GameState;
	bool shooting = false;
	//Face collidedObject;
	std::vector<GameObject*> enemies;
	std::vector<GameObject*> bullets;

	//ShaderProgram passThrough;
	ShaderProgram PhongNoTexture;
	//ShaderProgram Phong;
	ShaderProgram Phong;


	glm::mat4 cameraTransform;
	glm::mat4 cameraProjection;
	glm::vec3 playerPos, enemyPos;
	glm::vec3 hpScale;
	glm::vec4 exitGoal = glm::vec4(77.f, 81.f, 67.f, 70.f);

	//Mesh monkey;
	//Mesh level;
	//glm::mat4 monkeyTransform;
	//glm::mat4 monkeyRotate;
	//glm::mat4 monkeyTranslate;
	//float monkeyScale = 1.f;
	//glm::mat4 monkey2Transform;
	std::vector<glm::vec2> enemy1Loc =
	{ 
		{2.86804,	30.8909	},
		{32.4772, 47.1091},
		{63.368, 29.1091},
		{27.5863, 3.10911},
		{33.5863, 3.10911},
		{35.368, 9.10911},
		{29.5863, 8.89089},
		{57.368, 3.10911},
		{33.5863, 8.89089},
		{151.368, 20.8909},
		{127.368, 4.89089},
		{133.368, 4.89089},
		{113.368, 4.89089},
		{105.368, 4.89089},
		{87.5863, 2.89089},
		{135.368, 11.1091},
		{136.477, 42.0	},
		{132.477, 42.0	},
		{136.477, 46.0	},
		{98.4771, 64.0	},
		{102.477, 64.0	},
		{106.477, 64.0	},
		{76.4771, 34.0	},
		{80.4771, 34.0	} 
	};

	std::vector<glm::vec2> enemy2Loc =
	{
		{ 67.368, 15.1091 },
		{ 51.5863, 44.8909 },
		{ 151.586, 16.8909 },
		{ 151.368, 12.8909 },
		{ 141.368, 58.0 },
		{ 101.586, 64.0 },
		{ 102.477, 36.0 },
		{ 79.368, 64.0 }
	};

private:
	glm::vec2 windowSize;
	bool shouldRotate = false;
	bool wKeydown = false;
	bool aKeydown = false;
	bool sKeydown = false;
	bool dKeydown = false;
	bool oKeydown = false;
	bool pKeydown = false;
	bool collideW = true;
	bool collideA = true;
	bool collideS = true;
	bool collideD = true;
	bool collide2W = true;
	bool collide2A = true;
	bool collide2S = true;
	bool collide2D = true;
	// Distance before triggering enemy chase
	float triggerDist = 10.f;
};