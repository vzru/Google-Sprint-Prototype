
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
	//hitboxes.loadMesh("meshes/Laboratory Final Triangulated HitBoxes.obj");
	hitboxes.transform = glm::translate(hitboxes.transform, { 0, -5, 0 });
	player.loadMesh("meshes/character_model.obj");
	enemyLoadIn.loadMesh("meshes/enemy_model.obj");
	bullet.loadMesh("meshes/bullet.obj");

	level.loadMesh("meshes/Level.obj");
	//level.loadMesh("meshes/Laboratory Level Trianguated.obj");
	levelHitBox = LevelHitBox(PLAYER_RADIUS);
	levelHitBox.loadFromFile("meshes/Hitbox Base.obj");
	//levelHitBox.loadFromFile("meshes/Laboratory Final Base HitBoxes.obj");

	player.color = glm::vec4(1.f, 1.f, 1.f, 1.f);
	player.cd = 1.f;
	player.hp = 10.f;
	hitboxes.color = glm::vec4(1.f, 0.f, 0.f, 1.f);
	level.color = glm::vec4(0.f, 1.f, 0.f, 1.f);
	bullet.hp = 0.05f;
	bullet.color = glm::vec4(1.f, 1.f, 1.f, 1.f);


	player.translate = glm::translate(player.translate, { 11.f, 0.f, 11.f });
	//hitboxes.transform = glm::translate(hitboxes.transform, { 2.f, 0.f, 0.f });


	cameraTransform = glm::rotate(cameraTransform, glm::radians(70.0f), glm::vec3(1.f, 0.f, 0.f));
	cameraTransform = glm::translate(cameraTransform, glm::vec3(-11.f, -5.f, -12.18f));
	cameraProjection = glm::perspective(glm::radians(90.f),
		(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,
		0.1f, 10000.f);

	for (int i = 0; i < 5; i++)
	{
		GameObject* enemy = new GameObject(enemyLoadIn);
		enemy->color = glm::vec4(0.5f, 0.5f, 0.5f, 1.0f);
		enemy->translate = glm::translate(enemy->translate, { 15.f + i, 0.f, 15.f + i });
		enemy->hp = 5.f;
		enemies.push_back(enemy);
	}
}

void Game::update()
{
	//update timer so we have correct delta time since last update
	updateTimer->tick();

	float deltaTime = updateTimer->getElapsedTimeSec();

	if (clearLevel(exitGoal))
	{
		std::cout << "YOU WIN" << std::endl;
		//system("pause");
	}

	if (shooting)
	{
		//GameObject* bullet = new GameObject;
		//bullet.rotate = player.rotate;
		bullet.transform = player.transform;
		//bullet.transform = glm::translate(bullet.transform, glm::vec3(0.f, 1.f, 0.f));
		bullets.push_back(new GameObject(bullet));
		std::cout << "Bullet Created" << std::endl;
		shooting = false;
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->cd <= 0.f) {
			glm::vec3 rots = bullets[i]->transform[0];
			float bang = acos(rots[0]) * asin(rots[2]) / abs(asin(rots[2]));
			float distToEnemy = 1000.f;
			GameObject* enemy = nullptr;
			for (int j = 0; j < enemies.size(); j++)
			{
				glm::vec3 diff = enemies[j]->transform * glm::vec4(0.f, 0.f, 0.f, 1.f) - bullets[i]->transform * glm::vec4(0.f, 0.f, 0.f, 1.f);
				float dang = atan2(diff.z, diff.x);
				float dist = sin(bang - dang) * glm::length(diff);

				if (dist < 0.5f && dist > -0.5f)
				{
					if (distToEnemy > (cos(bang - dang) * glm::length(diff))) 
					{
						distToEnemy = cos(bang - dang) * glm::length(diff);
						if (distToEnemy > 0)
						{
							enemy = enemies[j];
						}
					}
				}
				std::cout << enemies[j]->hp << ';' << dist << ':' << distToEnemy << ':' << glm::degrees(bang) << std::endl;
			}
			if (enemy != nullptr) {
				enemy->hp--;
				bullets[i]->cd = 1.f;
			}
		}
		
		//std::cout << glm::degrees(acos(bullets[i]->transform[0][0]) * asin(bullets[i]->transform[0][2]) / abs(asin(bullets[i]->transform[0][2]))) << std::endl;
		bullets[i]->hp -= deltaTime;
		bullets[i]->cd -= deltaTime;
		if (bullets[i]->hp <= 0.f)
		{
			delete bullets[i];
			bullets.erase(i + bullets.begin());
			i--;
			std::cout << "Bullet Deleted" << std::endl;
		}
	}


	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->hp <= 0.f)
		{
			delete enemies[i];
			enemies.erase(i + enemies.begin());
			i--;
			std::cout << "Enemy Deleted" << std::endl;
		}
	}
	

	//std::cout << deltaTime << std::endl;
	if (shouldRotate)
	{
		player.rotate = glm::rotate(player.rotate,
			deltaTime * (glm::pi<float>() / 4.f),
			glm::vec3(0.f, 1.f, 0.f));
	}
	if (wKeydown)
	{
		if (collision2.colliding(player, levelHitBox.hitBoxes, collision.collidedObject) != 4 && collision2.CollidedDirection != 4)
		{
			if (collision.colliding(player, levelHitBox.hitBoxes, collision2.collidedObject) != 4 && collision.CollidedDirection != 4)
			{
				player.translate = glm::translate(player.translate, glm::vec3(0.f, 0.f, -deltaTime * 5));
				cameraTransform = glm::translate(cameraTransform, glm::vec3(0.f, 0.f, deltaTime * 5));
			}
		}
	}
	if (aKeydown)
	{
		if (collision2.colliding(player, levelHitBox.hitBoxes, collision.collidedObject) != 2 && collision2.CollidedDirection != 2)
		{
			if (collision.colliding(player, levelHitBox.hitBoxes, collision2.collidedObject) != 2 && collision.CollidedDirection != 2)
			{
				player.translate = glm::translate(player.translate, glm::vec3(-deltaTime * 5, 0.f, 0.f));
				cameraTransform = glm::translate(cameraTransform, glm::vec3(deltaTime * 5, 0.f, 0.f));
			}
		}
	}
	if (sKeydown)
	{

		if (collision2.colliding(player, levelHitBox.hitBoxes, collision.collidedObject) != 1 && collision2.CollidedDirection != 1)
		{
			if (collision.colliding(player, levelHitBox.hitBoxes, collision2.collidedObject) != 1 && collision.CollidedDirection != 1)
			{
				player.translate = glm::translate(player.translate, glm::vec3(0.f, 0.f, deltaTime * 5));
				cameraTransform = glm::translate(cameraTransform, glm::vec3(0.f, 0.f, -deltaTime * 5));
			}
		}
	}
	if (dKeydown)
	{
		if (collision2.colliding(player, levelHitBox.hitBoxes, collision.collidedObject) != 3 && collision2.CollidedDirection != 3)
		{
			if (collision.colliding(player, levelHitBox.hitBoxes, collision2.collidedObject) != 3 && collision.CollidedDirection != 3)
			{
				player.translate = glm::translate(player.translate, glm::vec3(deltaTime * 5, 0.f, 0.f));
				cameraTransform = glm::translate(cameraTransform, glm::vec3(-deltaTime * 5, 0.f, 0.f));
			}
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

		enemies[i]->translate = glm::translate(enemies[i]->translate, glm::vec3(deltaTime * glm::normalize(playerPos.x - enemyPos.x), 0.f, deltaTime * glm::normalize(playerPos.z - enemyPos.z)));

		enemies[i]->transform = enemies[i]->translate * enemies[i]->rotate;
		//enemies[i]->translate = glm::translate(enemies[i]->transform, enemyPos);
		if (player.cd <= 0.f)
		{
			if (glm::length(diff) < 1.f)
			{
				player.hp--;
				player.cd = 1.f;
			}
		}
	}
	// F = T * R * S;
	player.transform = player.translate * player.rotate * glm::scale(glm::mat4(), glm::vec3(player.scale));
	//std::cout << player.cd << ':' << player.hp << std::endl;
	if (player.hp <= 0.f)
	{
		std::cout << "YOU LOSE" << std::endl;
		system("pause");
	}
	player.cd -= deltaTime;
}

void Game::draw()
{
	glClearColor(0.f, 0.f, 0.f, 0.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	player.draw(Phong, cameraTransform, cameraProjection);
	level.draw(Phong, cameraTransform, cameraProjection);
	//hitboxes.draw(Phong, cameraTransform, cameraProjection);
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->draw(Phong, cameraTransform, cameraProjection);
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->draw(Phong, cameraTransform, cameraProjection);
		//glm::vec3 bulPos = bullets[i]->transform * glm::vec4(0.f, 0.f, 0.f, 1.f);
		//GLboolean lightingEnabled;
		//glGetBooleanv(GL_LIGHTING, &lightingEnabled);
		//
		//glDisable(GL_LIGHTING);
		//glLineWidth(5.0f);
		//glBegin(GL_LINES);
		//glColor3f(0.5f, 0.5f, 0.5f);
		//glVertex3f(bulPos.x, bulPos.y, bulPos.z);
		//glVertex3f(bulPos.x + 100.f, bulPos.y, bulPos.z);
		//glRotatef(glm::radians(acos(bullets[i]->transform[0][0])), 0, 1, 0);
		//glEnd();
		//glLineWidth(1.0f);
		//
		//if (lightingEnabled)
		//	glEnable(GL_LIGHTING);
		//std::cout << "Bullet Drawed :" << bulPos.x << '/' << bulPos.y << '/' << bulPos.z << std::endl;
	}


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
			shooting = true;
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

bool Game::clearLevel(glm::vec4 goal)
{
	glm::vec3 pos(player.transform * glm::vec4(0.f, 0.f, 0.f, 1.f));
	//std::cout << pos.x << '/' << pos.z << std::endl;
	//std::cout << goal.x << '/' << goal.y << '/' << goal.z << '/' << goal.w << std::endl;

	return (pos.x >= goal.x && pos.x <= goal.y && pos.z >= goal.z && pos.z <= goal.w);
}
