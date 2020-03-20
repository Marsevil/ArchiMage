#ifndef DRAWABLE_OBJECT_HPP
#define DRAWABLE_OBJECT_HPP

#include "../include/lib_objectsReader/objetsOFF.hpp"
#include "Drawable.hpp"
#include <iostream>

class DrawableObject : public off::Objet, public virtual Drawable
{
private:
	float * lcolors;
	GLuint colorsVBO;

public:
	DrawableObject();

	virtual void draw() const override;
	virtual void constructVBO() override;
	void changeColor(size_t index, float color[3]);
};

#endif /* end of include guard: DRAWABLE_OBJECT_HPP */
