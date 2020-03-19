#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/freeglut.h>

#include <iostream>
#include "../headers/DrawableObject.hpp"

DrawableObject* offLoader = nullptr;

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Edit projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0, 1.0, 0.1, 100);

	//Edit model matrix
	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	offLoader->draw();
}

void InitialiseGlutCallback() {
	glutDisplayFunc(renderScene);
}

void GlewInit() {
	GLenum err = glewInit();

	if (err != GLEW_OK) {
		std::cerr << "Erreur: " << glewGetErrorString(err) << std::endl;
	}

	std::cerr << "initGLEW_ok, ref GLEW" << glewGetString(GLEW_VERSION) << std::endl;

	if (glewIsSupported("GL_VERSION_2_0")) std::cerr << "ok OpenGL 2.0" << std::endl;
	else {
		std::cerr << "OpenGL 2.0 Impossible" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::cout << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "OpenGL Renderer " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
}

void geomInit() {
	offLoader = new DrawableObject();
	offLoader->charge_OFF("objects/sphere.off");
	offLoader->constructVBO();
}

void freeSpace() {
	delete offLoader;
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Lourd Projet Raffin");

	GlewInit();

	InitialiseGlutCallback();
	//InitialiseGL();
	//SetShaders();

	geomInit();

	glutMainLoop();

	freeSpace();
  return EXIT_SUCCESS;
}
