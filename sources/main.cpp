#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <list>
#include <random>
#include <algorithm>

// Gestion des shaders :
#include "lib_shaders/glsl_fs.hpp"
#include "lib_shaders/glsl_vs.hpp"
#include "lib_shaders/glsl_program.hpp"
#include "lib_shaders/fonctions.hpp"

#include <iostream>
#include "../headers/DrawableObject.hpp"

int oldMouseX = 0, oldMouseY = 0;
size_t activePoint = 0;
float mouseAngleX = 0.0, mouseAngleY = 0.0;
float xpos = 0, zpos = -1;

DrawableObject * offLoader = nullptr;

// ShaderManager :
GLSL_Program * shaders;

// Les adresses de ce qu'on va envoyer au GPU :
GLint addr_point;
GLint addr_color;
GLint addr_nb_triangles;
GLint addr_neighbors;

void findNewActivePoint() {
	std::list<int> neighbors;

	for (size_t i = 0; i < offLoader->nbfaces; ++i) {
		//Find neighbors of the activePoint.

		//If the 1rs point is the current point others are its neighbors.
		if (activePoint == offLoader->lfaces[i].S1) {
			neighbors.push_back(offLoader->lfaces[i].S2);
			neighbors.push_back(offLoader->lfaces[i].S3);
		}

		//The same if the 2nd point is the current.
		if (activePoint == offLoader->lfaces[i].S2) {
			neighbors.push_back(offLoader->lfaces[i].S1);
			neighbors.push_back(offLoader->lfaces[i].S3);
		}

		//And finally if the 3rd point is the current.
		if (activePoint == offLoader->lfaces[i].S3) {
			neighbors.push_back(offLoader->lfaces[i].S1);
			neighbors.push_back(offLoader->lfaces[i].S2);
		}
	}

	//Find a random number which will select the new activePoint.
	std::random_device rd;
	std::uniform_int_distribution<int> dist(0, neighbors.size() - 1);
	size_t chosenNeighbors = dist(rd);

	//Finally change the activePoint.
	std::list<int>::iterator it = neighbors.begin();
	for (size_t i = 0; i < chosenNeighbors; ++i) ++it;
	activePoint = *it;

	neighbors.clear();
}

void timer(int extra)
{
    glutPostRedisplay();
    glutTimerFunc(30, timer, 0);
}

void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Edit projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glRotatef(mouseAngleX, 0.0, 1.0, 0.0);
	glRotatef(mouseAngleY, 1.0, 0.0, 0.0);
	//glTranslatef(xpos, 0, zpos);

	//Edit model matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

	// Set Data :
	float point[3] = {float(offLoader->lpoints[activePoint].x), float(offLoader->lpoints[activePoint].y), float(offLoader->lpoints[activePoint].z)};
	float color[4] = {tirage_alea(0.0, 1.0), tirage_alea(0.0, 1.0), tirage_alea(0.0, 1.0), 1.0};


	// Send data to GPU :
	glUniform3fv(addr_point, 1, point);
	glUniform4fv(addr_color, 1, color);
	// Fabien :
	float nb_tmp = 2;
	float tri_tmp[9] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	glUniform1f(addr_nb_triangles, nb_tmp);
	glUniformMatrix3fv(addr_neighbors, 1, GL_FALSE, tri_tmp);


	offLoader->draw();

	glutSwapBuffers();
}

GLvoid callbackIdle() {
	glutPostRedisplay();
}

GLvoid callbackMouse(int wx, int wy) {
	mouseAngleX += oldMouseX - wx;
	mouseAngleY += oldMouseY - wy;

	oldMouseX = wx;
	oldMouseY = wy;
}

GLvoid callbackKeyboard(unsigned char key, int x, int y)
{
	switch (key) {
		case ' ':
			findNewActivePoint();
			break;

		default:
			std::cerr << "Key not binded" << std::endl;
	}
}

GLvoid callbackSpecialKey(int key, int x, int y) {
	switch (key) {
		case GLUT_KEY_UP:
			mouseAngleY++;
			break;
		case GLUT_KEY_DOWN:
			mouseAngleY--;
			break;
		case GLUT_KEY_LEFT:
			mouseAngleX++;
			break;
		case GLUT_KEY_RIGHT:
			mouseAngleX--;
			break;
		default:
			std::cerr << "Key not binded" << std::endl;
	}



}

void InitialiseGlutCallback() {
	glutDisplayFunc(renderScene);

	glutIdleFunc(callbackIdle);

	glutMotionFunc(callbackMouse);

	glutSpecialFunc(callbackSpecialKey);

	glutKeyboardFunc(callbackKeyboard);
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
	delete shaders;
	delete offLoader;
}

void SetShaders(void) {
	GLSL_VS color_vs;
	GLSL_FS color_fs;
	GLSL_VS normal_vs;

	color_vs.ReadSource("shaders/point_color.vert");
	color_vs.Compile();

	color_fs.ReadSource("shaders/point_color.frag");
	color_fs.Compile();

	normal_vs.ReadSource("shaders/processNormal.vert");

	PrintShaderInfo(color_vs.idvs);
	PrintShaderInfo(color_fs.idfs);
	PrintShaderInfo(normal_vs.idvs);

	shaders = new GLSL_Program();

	shaders->Use_VertexShader(normal_vs);
	shaders->Use_VertexShader(color_vs);
	shaders->Use_FragmentShader(color_fs);

	shaders->Link_Shaders();
	shaders->Activate();

	// Link :
	addr_point = glGetUniformLocation(shaders->idprogram, "cpu_point");
	addr_color = glGetUniformLocation(shaders->idprogram, "cpu_color");
	addr_nb_triangles = glGetUniformLocation(shaders->idprogram, "nbTriangle");
	addr_neighbors = glGetUniformLocation(shaders->idprogram, "triangles");

	PrintProgramInfo(shaders->idprogram);

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
	SetShaders();



	geomInit();


	glutMainLoop();


	freeSpace();

	return EXIT_SUCCESS;
}
