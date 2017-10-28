
#include "Game.h"
#include <iostream>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

Game::Game()
{

}

Game::~Game()
{
	delete updateTimer;
	Phong.unload();
}

void Game::initializeGame()
{
	updateTimer = new Timer();

	glEnable(GL_DEPTH_TEST);

	if (!Phong.load("shaders/Phong.vert", "shaders/PhongNoTexture.frag"))
	{
		std::cout << "Shaders failed to initialize." << std::endl;
		system("pause");
		exit(0);
	}


	player.loadMesh("meshes/character model.obj");
	level.loadMesh("meshes/twin box.obj");

	player.color = glm::vec4(1.f, 0.f, 0.f, 1.f);
	level.color = glm::vec4(0.f, 1.f, 0.f, 1.f);


	level.transform = glm::translate(level.transform, glm::vec3(3.f, 0.f, 0.f));

	cameraTransform = glm::rotate(cameraTransform, glm::radians(70.0f), glm::vec3(1.f, 0.f, 0.f));
	cameraTransform = glm::translate(cameraTransform, glm::vec3(0.f, -5.f, -1.82f));
	cameraProjection = glm::perspective(glm::radians(90.f),
		(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,
		0.1f, 10000.f);

}

void Game::update()
{
	//update timer so we have correct delta time since last update
	updateTimer->tick();

	float deltaTime = updateTimer->getElapsedTimeSec();

	if (shouldRotate)
	{
		player.rotate = glm::rotate(player.rotate,
			deltaTime * (glm::pi<float>() / 4.f),
			glm::vec3(0.f, 1.f, 0.f));
	}
	if (wKeydown)
	{
		if (!collision.collided(player, glm::vec2(2.5f, -0.5f), glm::vec2(3.5f, 0.5f)) || collision.collideX && collision.yDir || collision.collideY )
		{
			player.translate = glm::translate(player.translate, glm::vec3(0.f, 0.f, -deltaTime * 3));
			cameraTransform = glm::translate(cameraTransform, glm::vec3(0.f, 0.f, deltaTime * 3));
		}
	}
	if (aKeydown)
	{
		if (!collision.collided(player, glm::vec2(2.5f, -0.5f), glm::vec2(3.5f, 0.5f)) || collision.collideY && !collision.xDir || collision.collideX )
		{
			player.translate = glm::translate(player.translate, glm::vec3(-deltaTime * 3, 0.f, 0.f));
			cameraTransform = glm::translate(cameraTransform, glm::vec3(deltaTime * 3, 0.f, 0.f));
		}
	}
	if (sKeydown)
	{
		if (!collision.collided(player, glm::vec2(2.5f, -0.5f), glm::vec2(3.5f, 0.5f)) || collision.collideX && !collision.yDir || collision.collideY)
		{
			player.translate = glm::translate(player.translate, glm::vec3(0.f, 0.f, deltaTime * 3));
			cameraTransform = glm::translate(cameraTransform, glm::vec3(0.f, 0.f, -deltaTime * 3));
		}
	}
	if (dKeydown)
	{
		if (!collision.collided(player, glm::vec2(2.5f, -0.5f), glm::vec2(3.5f, 0.5f)) || collision.collideY && collision.xDir || collision.collideX)
		{
			player.translate = glm::translate(player.translate, glm::vec3(deltaTime * 3, 0.f, 0.f));
			cameraTransform = glm::translate(cameraTransform, glm::vec3(-deltaTime * 3, 0.f, 0.f));
		}
	}

	//collision.collided(player, glm::vec2(2.5f, -0.5f), glm::vec2(3.5f, 0.5f));
	//collision.collided(player, glm::vec2(2.5f, 1.5f), glm::vec2(3.5f, 2.5f));


	// F = T * R * S;
	player.transform = player.translate * player.rotate * glm::scale(glm::mat4(), glm::vec3(player.scale));
}

void Game::draw()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	player.draw(Phong, cameraTransform, cameraProjection);
	level.draw(Phong, cameraTransform, cameraProjection);

	glutSwapBuffers();
}

void Game::keyboardDown(unsigned char key, int mouseX, int mouseY)
{
	switch (key)
	{
	case 27: // esc key
	case 'q':
		exit(1);
		break;
	case 't':
		std::cout << "Total elapsed time: " << updateTimer->getCurrentTime() / 1000.0f << std::endl;
		break;
	case 'w':
		wKeydown = true;
		break;
	case 'a':
		aKeydown = true;
		break;
	case 's':
		sKeydown = true;
		break;
	case 'd':
		dKeydown = true;
		break;
	case 'o':
		oKeydown = true;
		break;
	case 'p':
		pKeydown = true;
		break;
	default:
		break;
	}
}

void Game::keyboardUp(unsigned char key, int mouseX, int mouseY)
{
	switch (key)
	{
	case 'r':
		shouldRotate = !shouldRotate;
		break;
	case 'w':
		wKeydown = false;
		break;
	case 'a':
		aKeydown = false;
		break;
	case 's':
		sKeydown = false;
		break;
	case 'd':
		dKeydown = false;
	case 'o':
		oKeydown = false;
	case 'p':
		pKeydown = false;
		break;
	default:
		break;
	}
}

void Game::mouseClicked(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		switch (button)
		{
		case GLUT_LEFT_BUTTON:
			// handle left click
			break;
		case GLUT_RIGHT_BUTTON:
			// handle right click
			break;
		case GLUT_MIDDLE_BUTTON:
			// handle middle click
			break;
		default:
			break;
		}
	}
}

void Game::mousePassive(int x, int y)
{
	player.rotate = glm::rotate(glm::mat4(),
		//updateTimer->getElapsedTimeSec() * glm::degrees(glm::dot(glm::vec2( 0.f, 1.f ), glm::normalize(glm::vec2( (float)(x - WINDOW_WIDTH/2), (float)(WINDOW_HEIGHT/2 - y) )))),
		(float)atan2(WINDOW_HEIGHT / 2 - y, x - WINDOW_WIDTH / 2),
		glm::vec3(0.f, 1.f, 0.f));
	//std::cout << glm::degrees((float)atan2(WINDOW_HEIGHT / 2 - y, x - WINDOW_WIDTH / 2)) << std::endl;
	//std::cout << glm::normalize(glm::vec2((float)x, (float)y)).x << " / " << glm::normalize(glm::vec2((float)x, (float)y)).y << std::endl;
	//std::cout << (x - WINDOW_WIDTH / 2)  << " / " << (WINDOW_HEIGHT / 2 - y) << std::endl;

}