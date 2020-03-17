//R. RAFFIN, IUT Aix-Marseille, département Informatique, site d'Arles
//M4104c, ARCHI IN
//romain.raffin[AT]univ-amu.fr

//une classe pour les VertexShader
#ifndef _GLSL_VS
#define _GLSL_VS

#include <GL/gl.h>

class GLSL_VS {
public:
	GLuint idvs;

	GLSL_VS(void);
	GLSL_VS(const GLSL_VS&);

	int ReadSource(const char *);
	int Compile();
};

#endif

