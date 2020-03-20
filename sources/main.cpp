#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/freeglut.h>
#include <list>
#include <random>

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

DrawableObject* offLoader = nullptr;

// ShaderManager :
GLSL_Program * shaders;

// Les adresses de ce qu'on va envoyer au GPU :
GLint addr_vertx;
GLint addr_verty;
GLint addr_vertz;
//GLint addr_point;
GLint addr_color;

size_t num_point = 0;

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

	//Finally change the activePoint.
	activePoint = dist(rd);
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

	// Set Data :
	//float point[3] = {offLoader->lpoints[num_point].x, offLoader->lpoints[num_point].y, offLoader->lpoints[num_point].z}; //offLoader->lpoints[0];
	float color[4] = {0.0, 1.0, 0.0, 1.0};

	// Send data to GPU :
	//glUniform3fv(addr_point, 1, point);
	off::point3D tmp = offLoader->lpoints[offLoader->lfaces[num_point].S1];
	float m_array[3] = {tmp.x, tmp.y, tmp.z};
	glUniform3fv(addr_vertx, 1, m_array);
	tmp = offLoader->lpoints[offLoader->lfaces[num_point].S2];
	m_array[0] = tmp.x; m_array[1] = tmp.y; m_array[2] = tmp.z;
	glUniform3fv(addr_verty, 1, m_array);
	tmp = offLoader->lpoints[offLoader->lfaces[num_point].S3];
	m_array[0] = tmp.x; m_array[1] = tmp.y; m_array[2] = tmp.z;
	glUniform3fv(addr_vertz, 1, m_array);
	glUniform4fv(addr_color, 1, color);
	num_point++;

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

GLvoid callbackSpecialKey(int key, int x, int y) {
	float speed = 1.0;

	switch (key) {
		case GLUT_KEY_UP:
			zpos += speed;
			break;
		case GLUT_KEY_DOWN:
			zpos -= speed;
			break;
		case GLUT_KEY_LEFT:
			xpos -= speed;
			break;
		case GLUT_KEY_RIGHT:
			xpos += speed;
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

	color_vs.ReadSource("shaders/point_color.vert");
	color_vs.Compile();

	color_fs.ReadSource("shaders/point_color.frag");
	color_fs.Compile();

	PrintShaderInfo(color_vs.idvs);
	PrintShaderInfo(color_fs.idfs);

	shaders = new GLSL_Program();

	shaders->Use_VertexShader(color_vs);
	shaders->Use_FragmentShader(color_fs);

	shaders->Link_Shaders();
	shaders->Activate();

	// Link :
	//addr_point = glGetUniformLocation(shaders->idprogram, "cpu_point");
	addr_color = glGetUniformLocation(shaders->idprogram, "cpu_color");
	addr_vertx = glGetUniformLocation(shaders->idprogram, "S1");
	addr_verty = glGetUniformLocation(shaders->idprogram, "S2");
	addr_vertz = glGetUniformLocation(shaders->idprogram, "S3");

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
	SetShaders();

	InitialiseGlutCallback();
	//InitialiseGL();


	geomInit();

	glutMainLoop();

	freeSpace();

	return EXIT_SUCCESS;
}
