#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <GL/glew.h>
#include <GL/gl.h>

class Drawable {
	GLuint VBO;

public:
	Drawable();
	~Drawable();

	virtual void draw() const = 0;
	virtual void constructVBO() = 0;

	inline GLuint const& vbo() const { return VBO; }
	inline GLuint& vbo() { return VBO; }
};

#endif /* end of include guard: DRAWABLE_HPP */
