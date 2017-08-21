#include <Windows.h>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <iostream>
#include "MyGlWindow.h"

using namespace std;

int main(int argc, char**  argv) {

	//initialization code
	glutInit(&argc, argv);	//This initializes glut
	glutInitWindowSize(640, 480);	//Width & height of display window
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Jamie King Tut 2 ");

	
	//Using a class method
	MyGLWindow myWindow;
	myWindow.initializeGL();
	
	while (true) {
		myWindow.paintGL();
		getchar();
	}

	glutMainLoop();
  
	return 0;
}
