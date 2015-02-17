#ifndef _MATHSTUFFANDSHIT_H_
#define _MATHSTUFFANDSHIT_H_

#include "glm/glm.hpp"
#include "GLFW/glfw3.h"

class MathStuffandShit
{
	public:

};

void Orthographic(float a_Left, float a_Right, float a_Top, float a_Bottom, float a_Near, float a_Far, glm::mat4 & mat);

double getDeltaTime();
void restDeltaTime();

#endif