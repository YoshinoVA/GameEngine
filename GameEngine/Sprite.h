#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "glew\glew.h"
#include "glew\wglew.h"
#include "soil/soil.h"
#include "glm/glm.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "tinyxml2.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <map>

struct vertex
{
	float Position[4];
	float color[4];
	float uv[2];
};

class Sprite
{
	public:
		Sprite(const char* a_file, int width, int height);
		Sprite();
		~Sprite();
		unsigned int LoadTexture(const char* a_Texture);
		unsigned int spriteID;
		void Draw();
		float x = 25;
		float y = 25;
		vertex vertices[4];
		GLuint uiShaderProg;
		GLuint uiVBO;
		GLuint uiIBO;
		GLuint uiVAO;
		GLuint TexThing;

		GLuint texLocation;
};

#endif