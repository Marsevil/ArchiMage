#ifndef DRAWABLE_OBJECT_HPP
#define DRAWABLE_OBJECT_HPP

#include "lib_objectsReader/objetsOFF.h"
#include "Drawable.hpp"

class DrawableObject : public Objet, public Drawable {
public:
	DrawableObject();

	virtual void draw() const;
	virtual void constructVBO() const;
};

#endif /* end of include guard: DRAWABLE_OBJECT_HPP */
