#ifndef _MATHSTUFFANDSHIT_H_
#define _MATHSTUFFANDSHIT_H_

#include "glm/glm.hpp"
#include "glew/glew.h"
#include "GLFW/glfw3.h"
#include "Sprite.h"

class MathStuffandShit
{
	public:

};

const float* getOrthograph(float a_Left, float a_Right, float a_Top, float a_Bottom, float a_Near, float a_Far);

double getDeltaTime();
void restDeltaTime();

#endif