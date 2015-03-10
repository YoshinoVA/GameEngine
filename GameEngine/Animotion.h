#ifndef _ANIMATION_H_
#define _ANIMATION_H_
#include <map>
#include "sprite.h"
#include "tinyxml2.h"

class Sprite;

enum AnimationType
{
	walk,
	idle
};
struct frame
{
	unsigned int frameNumber;
	glm::vec2 One_uv;
	glm::vec2 Two_uv;
	glm::vec2 Three_uv;
	glm::vec2 Four_uv;
};
struct Atlas
{
	float width, height;
	std::string sSheet;
	std::string sAnimations;
};
struct AniSprite
{
	std::string Name;
	float width, height;
	float x0, x1, y0, y1;
};
class Animotion
{
public:
	double currentFrame, deltaTime, lastFrame = 0;
	std::vector<Sprite> SpriteList;
	std::map<std::string, AniSprite> sprites;
	std::map<std::string, frame> animotion;
	unsigned int spriteID;
	unsigned int CreateSprite(const char* a_fileName, int width, int height, unsigned int shader);
	void DrawSprite(unsigned int s);
	void MoveSprite(unsigned int s, float x, float y);
	void LoadSprite(const char* a_SpriteSheet);
	void UpdateVertex(unsigned int s);
	void UpdateAnimotion();

	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement *docAtlas, *firstElement, *siblingElement;

	Atlas atlas;

	void loadAnimotionUV(const char* a_File, AnimationType currentState);
	void playAnimation(AnimationType desiredState);
	void createAnimotion(const char* a_File, AnimationType currentState, float width, float height);

	void dumptostdout(const char* a_File);
};

#endif