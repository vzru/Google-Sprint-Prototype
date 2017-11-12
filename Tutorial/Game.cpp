
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
	
	hitboxes.loadMesh("meshes/Hitbox Triangle.obj");
	hitboxes.transform = glm::translate(hitboxes.transform, { 0, -5, 0 });
	player.loadMesh("meshes/character_model.obj");
	enemyLoadIn.loadMesh("meshes/enemy_model.obj");
	
	level.loadMesh("meshes/Level.obj");
	levelHitBox = LevelHitBox(PLAYER_RADIUS);
	levelHitBox.loadFromFile("meshes/Hitbox Base.obj");

	player.color = glm::vec4(1.f, 1.f, 1.f, 1.f);
	hitboxes.color = glm::vec4(1.f, 0.f, 0.f, 1.f);
	level.color = glm::vec4(0.f, 1.f, 0.f, 1.f);
	

	player.translate = glm::translate(player.translate, { 11.f, 0.f, 11.f });
	hitboxes.transform = glm::translate(hitboxes.transform, { 2.f, 0.f, 0.f });
	

	cameraTransform = glm::rotate(cameraTransform, glm::radians(70.0f), glm::vec3(1.f, 0.f, 0.f));
	cameraTransform = glm::translate(cameraTransform, glm::vec3(-11.f, -15.f, -12.18f));
	cameraProjection = glm::perspective(glm::radians(90.f),
		(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,
		0.1f, 10000.f);

	for (int i = 0; i < 10; i++)
	{
		GameObject* enemy = new GameObject(enemyLoadIn);
		enemy->color = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
		enemy->translate = glm::translate(enemy->translate, { 15.f + i, 0.f, 15.f + i });
		enemies.push_back(enemy);
	}
}

void Game::update()
{
	//update timer so we have correct delta time since last update
	updateTimer->tick();

	float deltaTime = updateTimer->getElapsedTimeSec();

	//std::cout << deltaTime << std::endl;
	if (shouldRotate)
	{
		player.rotate = glm::rotate(player.rotate,
			deltaTime * (glm::pi<float>() / 4.f),
			glm::vec3(0.f, 1.f, 0.f));
	}
	if (wKeydown)
	{
			if (collision.collidedBottom(player, levelHitBox.hitBoxes) != 4 && collision.CollidedDirection != 4)
			{
				player.translate = glm::translate(player.translate, glm::vec3(0.f, 0.f, -deltaTime * 5));
				cameraTransform = glm::translate(cameraTransform, glm::vec3(0.f, 0.f, deltaTime * 5));
			}
	}
	if (aKeydown)
	{
			if (collision.collidedRight(player, levelHitBox.hitBoxes) != 2 && collision.CollidedDirection != 2)
			{
				player.translate = glm::translate(player.translate, glm::vec3(-deltaTime * 5, 0.f, 0.f));
				cameraTransform = glm::translate(cameraTransform, glm::vec3(deltaTime * 5, 0.f, 0.f));
			}
	}
	if (sKeydown)
	{

			if (collision.collidedTop(player, levelHitBox.hitBoxes) != 1 && collision.CollidedDirection != 1)
			{
				player.translate = glm::translate(player.translate, glm::vec3(0.f, 0.f, deltaTime * 5));
				cameraTransform = glm::translate(cameraTransform, glm::vec3(0.f, 0.f, -deltaTime * 5));
			}
	}
	if (dKeydown)
	{
			if (collision.collidedLeft(player, levelHitBox.hitBoxes) != 3 && collision.CollidedDirection != 3)
			{
				player.translate = glm::translate(player.translate, glm::vec3(deltaTime * 5, 0.f, 0.f));
				cameraTransform = glm::translate(cameraTransform, glm::vec3(-deltaTime * 5, 0.f, 0.f));
			}
	}

	//collision.collided(player, glm::vec2(2.5f, -0.5f), glm::vec2(3.5f, 0.5f));
	//collision.collided(player, glm::vec2(2.5f, 1.5f), glm::vec2(3.5f, 2.5f));
	playerPos = player.transform * glm::vec4(0.f, 0.f, 0.f, 1.f);

	for (unsigned int i = 0; i < enemies.size(); i++)
	{
		enemyPos = enemies[i]->transform * glm::vec4(0.f, 0.f, 0.f, 1.f);
		
		glm::vec3 diff = playerPos - enemyPos;
		enemies[i]->rotate = glm::rotate(glm::mat4(), glm::radians(90.f) + atan2f(-diff.z, diff.x), { 0, 1, 0 });

		//enemies[i]->translate = glm::translate(enemies[i]->transform, enemyPos);
		enemies[i]->translate = glm::translate(enemies[i]->translate, glm::vec3(deltaTime * glm::normalize(playerPos.x - enemyPos.x), 0.f, deltaTime * glm::normalize(playerPos.z - enemyPos.z)));

		enemies[i]->transform = enemies[i]->translate * enemies[i]->rotate;
	}
	// F = T * R * S;
	player.transform = player.translate * player.rotate * glm::scale(glm::mat4(), glm::vec3(player.scale));
}

void Game::draw()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	player.draw(Phong, cameraTransform, cameraProjection);
	level.draw(Phong, cameraTransform, cameraProjection);
	hitboxes.draw(Phong, cameraTransform, cameraProjection);
	for (int i = 0; i < enemies.size(); i++)
	enemies[i]->draw(Phong, cameraTransform, cameraProjection);


	//std::cout << levelHitBox.hitBoxes[0].min.x << '/' << levelHitBox.hitBoxes[0].min.y << ':' << levelHitBox.hitBoxes[0].max.x << '/' << levelHitBox.hitBoxes[0].max.y << std::endl;
	//glColor3f(1.0f, 1.0f, 1.0f);
	//glBegin(GL_POLYGON);
	//glVertex3f(levelHitBox.hitBoxes[0].min.x, -7.0, levelHitBox.hitBoxes[0].min.y);
	//glVertex3f(levelHitBox.hitBoxes[0].max.x, -7.0, levelHitBox.hitBoxes[0].min.y);
	//glVertex3f(levelHitBox.hitBoxes[0].max.x, -7.0, levelHitBox.hitBoxes[0].max.y);
	//glVertex3f(levelHitBox.hitBoxes[0].min.x, -7.0, levelHitBox.hitBoxes[0].max.y);
	//glEnd();
	//glFlush();

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
	case 'w': case 'W':
		wKeydown = true;
		break;
	case 'a': case 'A':
		aKeydown = true;
		break;
	case 's': case 'S':
		sKeydown = true;
		break;
	case 'd': case 'D':
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
	case 'w': case 'W':
		wKeydown = false;
		break;
	case 'a': case 'A':
		aKeydown = false;
		break;
	case 's': case 'S':
		sKeydown = false;
		break;
	case 'd': case 'D':
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