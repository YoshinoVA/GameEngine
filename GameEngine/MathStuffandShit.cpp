#include "MathStuffandShit.h"

void MathStuff::getOrtho(float left, float right, float bottom, float top, float a_fNear, float a_fFar, glm::mat4 & mat)
{
	float deltaX = right - left;
	float deltaY = top - bottom;
	float deltaZ = a_fNear - a_fFar;

	mat[0].x = 2.f / deltaX;
	mat[0].y = 0.f;
	mat[0].z = 0.f;
	mat[0].w = 0.f;

	mat[1].x = 0.f;
	mat[1].y = 2.f / deltaY;
	mat[1].z = 0.f;
	mat[1].w = 0.f;

	mat[2].x = 0.f;
	mat[2].y = 0.f;
	mat[2].z = 2.f / deltaZ;
	mat[2].w = 0.f;

	mat[3].x = ((left + right) / (left - right));
	mat[3].y = ((bottom + top) / (bottom - top));
	mat[3].z = (-(a_fNear + a_fFar) / (a_fFar - a_fNear));
	mat[3].w = 1.f;
}

void MathStuff::Perspective(float a_UpFOV, float a_AspectRatio, float a_fNear, float a_fFar, glm::mat4 & mat)
{
	mat = glm::perspective(a_UpFOV, a_AspectRatio, a_fNear, a_fFar);
}
