#include "../headers/DrawableObject.hpp"

DrawableObject::DrawableObject() : Drawable(), Objet()
{

}

DrawableObject::~DrawableObject()
{

}

void DrawableObject::draw() const {
	glEnableClientState(GL_VERTEX_ARRAY);

	// Select the current vbo.
	glBindBuffer(GL_ARRAY_BUFFER, vbo());
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, nbfaces * 3);
	glDrawArrays(/*GL_TRIANGLES*/GL_POINTS, 0, nbfaces * 3);
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
}
