//R. RAFFIN, IUT Aix-Marseille, département Informatique, site d'Arles
//M4104c, ARCHI IN
//romain.raffin[AT]univ-amu.fr

//une classe pour les fragment shaders
#include <cstdlib>
#include <GL/glew.h>

#include "glsl_fs.h"
#include "fonctions.h"

GLSL_FS::GLSL_FS(void) {
	idfs = glCreateShader(GL_FRAGMENT_SHADER);
}

GLSL_FS::GLSL_FS(const GLSL_FS & _copie) {
	idfs = _copie.idfs;
}

int GLSL_FS::ReadSource(const char* _filename) {

char * pointeur_source;
const char * constFS;

	if (ReadSourceFile(_filename, &pointeur_source) > 0) {
		constFS = pointeur_source;
		glShaderSource(idfs, 1, &constFS, NULL);
		delete [] pointeur_source;
	}

return 0;
}

int GLSL_FS::Compile() {
	glCompileShader(idfs);
	return EXIT_SUCCESS;
}


