#ifndef _ANIMATION_H_
#define _ANIMATION_H_
#include <map>
#include "sprite.h"
#include "tinyxml2.h"

class Sprite;

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

class Animotion
{
public:
	int hDirection, vDirection;
	double currentFrame, deltaTime, lastFrame = 0;
	std::vector<Sprite> SpriteList;
	unsigned int CreateSprite(const char* a_fileName, int width, int height,unsigned int shader);
	void DrawSprite(unsigned int s);
	void MoveSprite(unsigned int s, float x, float y);
	void UpdateVertex(unsigned int s);
	void UpdateAnimotion(unsigned int s);

	std::vector<frame> FramesAnimated;
	std::map<AnimationType, std::vector<frame>>MappedFrames;
	std::map<AnimationType, Sprite> AnimatingSpriteMap;

	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement * docAtlas, *firstElement, *siblingElement;

	void loadAnimotionUV(const char* a_File, AnimationType currentState);
	void playAnimation(AnimationType desiredState);

	void dumptostdout(const char* a_File);
};

#endif