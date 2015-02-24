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
#include <map>

struct vertex
{
	float Position;
	float color;
	float uv;
};

class Sprite
{
	public:
		Sprite(const char* a_file, int width, int height);
		Sprite(const char* a_File);
		Sprite();
		~Sprite();
		int spriteID;
		unsigned int loadTexture(const char* a_file, int & a_width, int & a_height, int & a_BPP);
		void Draw();
		int bpp;
		float x, y, sWidth, sHeight;
		std::vector<glm::vec2> UVlist;
		GLuint uiVBO;
		GLuint uiIBO;
};

#endif