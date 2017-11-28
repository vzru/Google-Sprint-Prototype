
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
	passThrough.unload();
	PhongNoTexture.unload();
	Phong.unload();
	PhongColorSides.unload();
	//monkey.unload();
}

void Game::initializeGame()
{
	updateTimer = new Timer();

	glEnable(GL_DEPTH_TEST);

	Light light1, light2;
	light1.positionDirection = glm::vec4(0.f, 4.f, 0.f, 1.f);
	light1.originalPosition = light1.positionDirection;
	light1.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
	light1.diffuse = glm::vec3(0.7f, 0.7f, 0.7f);
	light1.specular = glm::vec3(1.f, 1.f, 1.f);
	light1.specularExponent = 50.f;
	light1.constantAttenuation = 1.f;
	light1.linearAttenuation = 0.1f;
	light1.quadraticAttenuation = 0.01f;

	light2.positionDirection = glm::vec4(0.f, -4.f, 0.f, 1.f);
	light2.originalPosition = light2.positionDirection;
	light2.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
	light2.diffuse = glm::vec3(0.7f, 0.7f, 0.7f);
	light2.specular = glm::vec3(1.f, 1.f, 1.f);
	light2.specularExponent = 50.f;
	light2.constantAttenuation = 1.f;
	light2.linearAttenuation = 0.1f;
	light2.quadraticAttenuation = 0.01f;

	pointLights.push_back(light1);
	pointLights.push_back(light2);

	directionalLight.positionDirection = glm::vec4(-1.f, -1.f, -1.f, 1.f);
	directionalLight.ambient = glm::vec3(0.05f);
	directionalLight.diffuse = glm::vec3(0.7f);
	directionalLight.specular = glm::vec3(1.f);

	directionalLight.specularExponent = 50.f;

	if (!Phong.load("shaders/Phong.vert", "shaders/Phong.frag"))
	{
		std::cout << "Shaders failed to initialize." << std::endl;
		system("pause");
		exit(0);
	}

	if (!PhongColorSides.load("shaders/PhongColorSides.vert", "shaders/PhongColorSides.frag"))
	{
		std::cout << "Shaders failed to initialize." << std::endl;
		system("pause");
		exit(0);
	}

	Mesh monkey;
	if (!monkey.loadFromFile("meshes/monkey.obj"))
	{
		std::cout << "Model failed to load." << std::endl;
		system("pause");
		exit(0);
	}


	//monkey1 = GameObject(monkey);
	monkey1.loadMesh("meshes/Cube.obj");
	monkey1.loadTexture(TextureType::Diffuse, "textures/fur.png");
	monkey1.loadTexture(TextureType::Specular, "textures/fullSpecular.png");
	monkey1.loadTexture(TextureType::Normal, "textures/normal.jpg");
	//monkey2 = GameObject(monkey);
	monkey2.loadMesh("meshes/monkey.obj");
	monkey2.loadTexture(TextureType::Diffuse, "textures/fur.png");
	monkey2.loadTexture(TextureType::Specular, "textures/monkeySpecular.png");

	//monkey1.color = glm::vec4(1.f, 0.f, 0.f, 1.f);
	//monkey2.color = glm::vec4(0.f, 0.f, 1.f, 1.f);

	//cube.loadMesh("meshes/cube.obj");

	monkey2.transform = glm::translate(monkey2.transform, glm::vec3(3.f, 0.f, 0.f));

	//if (!monkey2.loadFromFile("meshes/Monkey.obj"))
	//{
	//	std::cout << "Model failed to load." << std::endl;
	//	system("pause");
	//	exit(0);
	//}
	//

	cameraTransform = glm::translate(cameraTransform, glm::vec3(0.f, 0.f, -5.f));
	cameraProjection = glm::perspective(45.f,
		(float)WINDOW_WIDTH / (float)WINDOW_HEIGHT,
		0.1f, 10000.f);

	//monkey.loadFromFile("meshes/Monkey.obj");
	//
	//std::cout << "Monkey faces: " << monkey.getNumFaces() << 
	//	" Vertices: " << monkey.getNumVertices() << std::endl;
	//
	//system("pause");
	//
	//monkey.unload();
	//
	//std::cout << "unloaded." << std::endl;
}

void Game::update()
{
	//update timer so we have correct delta time since last update
	updateTimer->tick();

	float deltaTime = updateTimer->getElapsedTimeSec();

	if (shouldRotate)
	{
		monkey1.rotate = glm::rotate(monkey1.rotate,
			deltaTime * (glm::pi<float>() / 4.f),
			glm::vec3(0.f, 1.f, 0.f));
	}
	if (wKeydown)
	{
		monkey1.translate = glm::translate(monkey1.translate, glm::vec3(0.f, deltaTime, 0.f));
	}
	if (aKeydown)
	{
		monkey1.translate = glm::translate(monkey1.translate, glm::vec3(-deltaTime, 0.f, 0.f));
	}
	if (sKeydown)
	{
		monkey1.translate = glm::translate(monkey1.translate, glm::vec3(0.f, -deltaTime, 0.f));
	}
	if (dKeydown)
	{
		monkey1.translate = glm::translate(monkey1.translate, glm::vec3(deltaTime, 0.f, 0.f));
	}
	if (oKeydown)
	{
		monkey1.scale -= deltaTime;
	}
	if (pKeydown)
	{
		monkey1.scale += deltaTime;
	}
	if (monkey1.scale <= 0.f)
	{
		monkey1.scale = 0.f;
	}
	if (shouldLightsSpin)
	{
		lightSpinner = glm::rotate(lightSpinner, deltaTime * (glm::pi<float>() / 2.f), glm::vec3(0.f, 0.f, 1.f));

		for (int i = 0; i < pointLights.size(); i++)
		{
			pointLights[i].positionDirection = lightSpinner * pointLights[i].originalPosition;
		}
		
	}
	// F = T * R * S;
	monkey1.transform = monkey1.translate * monkey1.rotate * glm::scale(glm::mat4(), glm::vec3(monkey1.scale));
}

void Game::draw()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	monkey1.draw(Phong, cameraTransform, cameraProjection, pointLights,directionalLight);
	monkey2.draw(Phong, cameraTransform, cameraProjection, pointLights,directionalLight);

	//PhongNoTexture.unbind();
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
	case 'l':
		shouldLightsSpin = !shouldLightsSpin;
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
		break;
	case 'o':
		oKeydown = false;
		break;
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

void Game::mouseMoved(int x, int y)
{
}