#include "../headers/DrawableObject.hpp"

DrawableObject::DrawableObject() : Drawable(), Objet()
{

}

void DrawableObject::draw() const {
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	// Select the current vbo.
	glBindBuffer(GL_ARRAY_BUFFER, vbo());
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glColorPointer(3, GL_FLOAT, 0, (char *) NULL );

	glBindBuffer( GL_ARRAY_BUFFER, colorsVBO);
	glNormalPointer(GL_FLOAT, 0, (char *) NULL );

	glDrawArrays(GL_TRIANGLES, 0, nbfaces * 3);

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void DrawableObject::constructVBO() {

	//Create a list of vertex without index just to send to GPU.
	float * lSommets = new float[nbfaces * 9];

	for (unsigned int i = 0, cpt = 0; i < nbfaces; ++i) {
		//1st vertex
		lSommets[cpt++] = lpoints[lfaces[i].S1].x;
		lSommets[cpt++] = lpoints[lfaces[i].S1].y;
		lSommets[cpt++] = lpoints[lfaces[i].S1].z;

		//2nd vertex
		lSommets[cpt++] = lpoints[lfaces[i].S2].x;
		lSommets[cpt++] = lpoints[lfaces[i].S2].y;
		lSommets[cpt++] = lpoints[lfaces[i].S2].z;

		//3rd vertex
		lSommets[cpt++] = lpoints[lfaces[i].S3].x;
		lSommets[cpt++] = lpoints[lfaces[i].S3].y;
		lSommets[cpt++] = lpoints[lfaces[i].S3].z;
	}

	// Triangles :
	glBindBuffer(GL_ARRAY_BUFFER, vbo());
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * nbfaces * 9, lSommets, GL_STATIC_DRAW);

	lcolors = new float[nbfaces * 9];

	for (unsigned int i = 0, cpt = 0; i < nbfaces; ++i) {
		lcolors[cpt++] = 1.0;
		lcolors[cpt++] = 1.0;
		lcolors[cpt++] = 1.0;

		lcolors[cpt++] = 1.0;
		lcolors[cpt++] = 1.0;
		lcolors[cpt++] = 1.0;

		lcolors[cpt++] = 1.0;
		lcolors[cpt++] = 1.0;
		lcolors[cpt++] = 1.0;
	}

	glGenBuffers((GLsizei) 1, &colorsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, nbfaces * 9 * sizeof(float), lcolors, GL_STATIC_DRAW);
}


void DrawableObject::changeColor(size_t index, float color[3])
{
	index *= 3;
	if (index + 2 < nbfaces * 9)
	{
		lcolors[index++] = color[0];
		lcolors[index++] = color[1];
		lcolors[index] = color[2];
	}

	glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
	glBufferData(GL_ARRAY_BUFFER, nbfaces * 9 * sizeof(float), lcolors, GL_STATIC_DRAW);
}
