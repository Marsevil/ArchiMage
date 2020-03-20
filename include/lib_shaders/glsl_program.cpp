//R. RAFFIN, IUT Aix-Marseille, département Informatique, site d'Arles
//M4104c, ARCHI IN
//romain.raffin[AT]univ-amu.fr

//une classe pour les ShaderProgram
#include <GL/glew.h>

#include "glsl_program.hpp"

GLSL_Program::GLSL_Program(void) {
	idprogram = glCreateProgram();
}

GLSL_Program::GLSL_Program(const GLSL_Program& _copie) {
	idprogram = _copie.idprogram;
}

GLSL_Program::~GLSL_Program() {
//rien
}

void GLSL_Program::Use_FragmentShader(GLSL_FS& _fs) {
	glAttachShader(idprogram, _fs.idfs);
}

void GLSL_Program::Use_VertexShader(GLSL_VS& _vs) {
	glAttachShader(idprogram, _vs.idvs);
}

void GLSL_Program::Link_Shaders() {
	glLinkProgram(idprogram);
}

void GLSL_Program::Activate() {
	glUseProgram(idprogram);

}

void GLSL_Program::Deactivate() {
	//rien pour l'instant
}
