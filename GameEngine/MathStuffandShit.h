#ifndef _MATHSTUFFANDSHIT_H_
#define _MATHSTUFFANDSHIT_H_

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp" 
#include "glew/glew.h"
#include "GLFW/glfw3.h"
#include "Sprite.h"
#include <vector>

class MathStuff
{
	public:
		static void getOrtho(float a_Left, float a_Right, float a_Top, float a_Bottom, float a_Near, float a_Far, glm::mat4 & mat);
		static void Perspective(float a_UpFOV, float a_AspectRatio, float a_fNear, float a_fFar, glm::mat4 & mat);

};

#endif