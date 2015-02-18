#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "glew\glew.h"
#include "glew\wglew.h"
#include "GLFW\glfw3.h"
#include <map>

// forward declaration
class InputHandler;

struct CharValues
{
	unsigned int id, x0, y0, x1, y1, width, height, xOffset, yOffset, xAdvance, scaleH;
};
#endif