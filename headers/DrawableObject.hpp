#ifndef DRAWABLE_OBJECT_HPP
#define DRAWABLE_OBJECT_HPP

#include "../include/lib_objectsReader/objetsOFF.hpp"
#include "Drawable.hpp"

class DrawableObject : public off::Objet, public virtual Drawable {
public:
	DrawableObject();

	virtual void draw() const override;
	virtual void constructVBO() const override;
};

#endif /* end of include guard: DRAWABLE_OBJECT_HPP */
