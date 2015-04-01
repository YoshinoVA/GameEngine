#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "glew\glew.h"
#include "glew\wglew.h"
#include "soil/soil.h"
#include "glm\glm.hpp"
#include "glm\gtc\type_ptr.hpp"
#include "glm\matrix.hpp"
#include "tinyxml2.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include "Animotion.h"
#include <ctime>
#include "time.h"

class GraphNode;

struct vertex
{
	float Position[4];
	float color[4];
	float uv[2];
};

class Sprite
{
	public:
		Sprite(const char* a_file, float xPos, float yPos, float newWidth, float newHeight);
		Sprite();
		~Sprite();
		unsigned int LoadTexture(const char* a_Texture);
		unsigned int spriteID;
		void Draw();
		float x;
		float y;
		float width;
		float height;
		void makeGrid();
		vertex vertices[4];
		Animotion * aniMate;
		GLuint uiShaderProg;
		GLuint uiVBO;
		GLuint uiIBO;
		GLuint uiVAO;
		GLuint TexThing;

		GLuint texLocation;
};
class Tank: public Sprite
{
public:
	Tank(const char* a_file, float xPos, float yPos, float newWidth, float newHeight);
	Tank();
	~Tank();
	glm::vec2 Velocity;
	float maxVelocity = 100;
	void Update();
	void Seek();

	//GraphNode * Node;
	std::vector<GraphNode *> path;	// the path we need to go
	int currentIndex = 0;		// index of the node in the path
};
#endif