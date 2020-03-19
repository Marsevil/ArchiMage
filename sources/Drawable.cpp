#include "../headers/Drawable.hpp"

Drawable::Drawable() : VBO(0) {
	glGenBuffers(1, &VBO);
}
