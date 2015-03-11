#ifndef _ANIMATION_H_
#define _ANIMATION_H_
#include <map>
#include "glew\glew.h"
#include "glfw\glfw3.h"
#include "sprite.h"
#include "tinyxml2.h"

class Sprite;

enum AnimationType
{
	walk,
	idle
};
enum PlayType
{
	ONCE,
	LOOP,
	LOOPSECTION,
	REVERSE,
	RANDOMLOOP,
	RANDOM,
	SINGLE
};

typedef std::vector<std::string> frame;

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
	double deltaTime, lastFrame = 0;
	std::vector<Sprite> SpriteList;
	std::map<std::string, AniSprite> sprites;
	std::map<std::string, frame> animotion;
	std::string currentAnimotion, currentSprite;
	int currentFrame;
	int loopFrame;
	
	unsigned int CreateSprite(const char* a_fileName, int width, int height, unsigned int shader);
	void DrawSprite();
	void MoveSprite(float x, float y);
	void setSprite();
	void ImportSheet(const char* a_SpriteSheet);
	void LoadSprite(const char* a_SpriteSheet);
	void LoadAnimations(const char* a_AnimationSheet);
	void UpdateVertex();
	void UpdateAnimotion();
	PlayType currentPlayType;

	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement *docAtlas, *firstElement, *siblingElement;

	Atlas atlas;
	Sprite * sprite;

	void setAnimation(std::string animation, PlayType type);
	void setAnimotion(std::string animation, PlayType type, int a_frame);
	void playAnimation();

	double elapsedTime = 0;

	void dumptostdout(const char* a_File);
};

double getDeltaTime();
void resetDeltaTime();

#endif