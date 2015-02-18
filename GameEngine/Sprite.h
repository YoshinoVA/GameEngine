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

enum AnimationType
{
	walk,
	idle,
};

struct frame
{
	unsigned int frameNumber;
	glm::vec2 One_uv;
	glm::vec2 Two_uv;
	glm::vec2 Three_uv;
	glm::vec2 Four_uv;
};

struct vertex
{
	glm::vec4 Position;
	float UVx, UVy, UVz, UVw;
	glm::vec4 color;
	glm::vec2 uv;
};

class Sprite
{
	public:
		Sprite(const char* a_file, int width, int height);
		Sprite(const char* a_File);
		~Sprite();
		vertex vertices[4];
		int spriteID;
		unsigned int loadTexture(const char* a_file, int & a_width, int & a_height, int & a_BPP);
		void Draw();
		int bpp;
		float x, y, sWidth, sHeight;
		std::vector<glm::vec2> UVlist;
		GLuint uiVBO;
		GLuint uiIBO;

		void UpdateUV(glm::vec2 vOne, glm::vec2 vTwo, glm::vec2 vThree, glm::vec2 vFour);
};

class Animotion
{
public:
	int hDirection, vDirection;
	double currentFrame, deltaTime, lastFrame = 0;
	std::vector<Sprite> SpriteList;
	unsigned int CreateSprite(const char* a_fileName, int width, int height);
	void DrawSprite(unsigned int s);
	void MoveSprite(unsigned int s, float x, float y);
	void UpdateVertex(unsigned int s);

	std::vector<frame> FramesAnimated;
	std::map<AnimationType, std::vector<frame>>MappedFrames;
	std::map<AnimationType, Sprite> AnimatingSpriteMap;

	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement * docAtlas, *firstElement, *siblingElement;

	void loadAnimotion(const char* a_File, AnimationType currentState);
	void playAnimation(AnimationType desiredState);

	void dump_to_stdout(const char* a_File);
};

#endif