#include <GL\glew.h>
#include <GL\glut.h>
#include <GL\freeglut.h>
#include <iostream>
#include "Game.h"
#include "Mesh.h"
#include "ShaderProgram.h"


const int FRAME_DELAY = 1000 / FRAMES_PER_SECOND;

Game* game;

void DisplayCallbackFunciton(void)
{
	game->draw();
}

void KeyboardDownCallbackFunction(unsigned char key, int x, int y)
{
	game->keyboardDown(key, x, y);
}

void KeyboardUpCallbackFunction(unsigned char key, int x, int y)
{
	game->keyboardUp(key, x, y);
}

void TimerCallbackFunction(int value)
{
	game->update();

	glutPostRedisplay();
	glutTimerFunc(FRAME_DELAY, TimerCallbackFunction, 0);
}

void WindowReshapeCallbackFunction(int width, int height)
{
	game->windowReshape(width, height);
}

void MouseClickCallbackFunction(int button, int state, int x, int y)
{
	game->mouseClicked(button, state, x, y);
}

void MousePassiveCallbackFunction(int x, int y)
{
	game->mousePassive(x, y);
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitContextVersion(4, 2);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 1600) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 1000) / 2);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("Tutorial");
	glutFullScreen();

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW could not be initialized." << std::endl;
		system("pause");
		return 0;
	}
	//glewInit();

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	glutDisplayFunc(DisplayCallbackFunciton);
	glutKeyboardFunc(KeyboardDownCallbackFunction);
	glutKeyboardUpFunc(KeyboardUpCallbackFunction);
	glutReshapeFunc(WindowReshapeCallbackFunction);
	glutMouseFunc(MouseClickCallbackFunction);
	glutPassiveMotionFunc(MousePassiveCallbackFunction);
	glutTimerFunc(1, TimerCallbackFunction, 0);

	game = new Game();
	game->initializeGame();

	glutMainLoop();

	return 0;
	system("pause");
}