#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <initializer_list>
#include <iostream>

inline GLfloat rgb2glf(unsigned char color)
{
	return color / 255.0f;
}

struct RGB
{
	GLfloat r, g, b;

	RGB(unsigned char _r, unsigned char _g, unsigned char _b);
};

