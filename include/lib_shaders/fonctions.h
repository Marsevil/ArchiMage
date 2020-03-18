//R. RAFFIN, IUT Aix-Marseille, département Informatique, site d'Arles
//M4104c, ARCHI IN
//romain.raffin[AT]univ-amu.fr

//quelques fonctions utiles pour les shaders (lecture de fichier, affichage d'erreurs GLSL, chargement d'une texture par Freeimage)
#ifndef _H_FONCTIONS
#define _H_FONCTIONS

#include <GL/gl.h>

void PrintProgramInfo(GLuint);
void PrintShaderInfo(GLuint);
int ReadSourceFile(const char*, char **);

#endif
