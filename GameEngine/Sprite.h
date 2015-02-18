#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "glew\glew.h"
#include "glew\wglew.h"
#include "soil/soil.h"
#include "glm/glm.hpp"
#include <vector>
#include <string>
#include <fstream>

struct vertex
{
	float PosX, PosY;
	float Rd, Gn, Bl, Al;
	float UVx, UVy, UVz, UVw;
	float color[4];
	float uv[4];
};

class Sprite
{
	public:
		Sprite(const char* a_file, float a_loc[2], int a_size[2], int a_BPP);
		Sprite(const char* a_File);
		~Sprite();
		vertex vertices[4];
		int spriteID;
		unsigned int loadTexture(const char* a_file, int & a_width, int & a_height, int & a_BPP);
		void Draw();
		int bpp;
		void Update(float a_DeltaTime);
		std::vector<glm::vec2> UVlist;
		GLuint uiVBO;
		GLuint uiIBO;

		void setUVdata();
};

#endif