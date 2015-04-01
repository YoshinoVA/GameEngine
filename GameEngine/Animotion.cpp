#include "animotion.h"
#include "sprite.h"

double deltaTime = 0;
int frames;
double fps, elapsedTime;

Animotion::Animotion()
{
	spriteScale = new glm::vec2();
}

Animotion::~Animotion()
{

}

void Animotion::dumptostdout(const char* a_File)
{
	tinyxml2::XMLDocument doc;

	int status = doc.LoadFile(a_File);

	if (status != tinyxml2::XML_NO_ERROR)
	{
		printf("God fucking damn it");
		doc.PrintError();
		return;
	}
	else
	{
		printf("Time to turn in a shit project");
	}
}
void Animotion::setSprite()
{
	if (currentAnimotion == "")
	{
		sprite->vertices[0].uv[0] = sprites["idle"].x1 / atlas.width;
		sprite->vertices[0].uv[1] = sprites["idle"].y1 / atlas.height;
		sprite->vertices[1].uv[0] = sprites["idle"].x0 / atlas.width;
		sprite->vertices[1].uv[1] = sprites["idle"].y1 / atlas.height;
		sprite->vertices[2].uv[0] = sprites["idle"].x1 / atlas.width;
		sprite->vertices[2].uv[1] = sprites["idle"].y0 / atlas.height;
		sprite->vertices[3].uv[0] = sprites["idle"].x0 / atlas.width;
		sprite->vertices[3].uv[1] = sprites["idle"].y0 / atlas.height;

		spriteScale->x = sprites[currentSprite].width;
		spriteScale->y = sprites[currentSprite].height;
	}
	else
	{
		sprite->vertices[0].uv[0] = sprites[currentSprite].x0 / atlas.width;
		sprite->vertices[0].uv[1] = sprites[currentSprite].y0 / atlas.height;
		sprite->vertices[1].uv[0] = sprites[currentSprite].x1 / atlas.width;
		sprite->vertices[1].uv[1] = sprites[currentSprite].y0 / atlas.height;
		sprite->vertices[2].uv[0] = sprites[currentSprite].x1 / atlas.width;
		sprite->vertices[2].uv[1] = sprites[currentSprite].y1 / atlas.height;
		sprite->vertices[3].uv[0] = sprites[currentSprite].x0 / atlas.width;
		sprite->vertices[3].uv[1] = sprites[currentSprite].y1 / atlas.height;
	}
}
void Animotion::ImportSheet(const char* a_SpriteSheet)
{
	LoadSprite(a_SpriteSheet);
	LoadAnimations(atlas.sAnimations.c_str());

	frames = (1.0 / 15.0);
	currentAnimotion = "";
	currentSprite = "idle";
	currentFrame = 0;
	currentPlayType = SINGLE;
	setSprite();
}
void Animotion::LoadSprite(const char* a_SpriteSheet)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode *rootNode, *currentNode;
	tinyxml2::XMLElement *childElement;
	std::string str;
	doc.LoadFile(a_SpriteSheet);
	rootNode = doc.FirstChildElement("atlas");
	currentNode = rootNode;

	childElement = currentNode->ToElement();
	atlas.width = (float)childElement->IntAttribute("width");
	atlas.height = (float)childElement->IntAttribute("height");
	atlas.sSheet = childElement->Attribute("sheet");
	atlas.sAnimations = childElement->Attribute("animotion");

	for (childElement = currentNode->FirstChildElement();
		childElement != NULL; childElement = childElement->NextSiblingElement())
	{
		str = childElement->Attribute("name");
		sprites[str].Name = str;
		sprites[str].x0 = childElement->IntAttribute("x0");
		sprites[str].x1 = childElement->IntAttribute("x1");
		sprites[str].y0 = childElement->IntAttribute("y0");
		sprites[str].y1 = childElement->IntAttribute("y1");
		sprites[str].height = sprites[str].y1 - sprites[str].y0;
		sprites[str].width = sprites[str].x1 - sprites[str].x0;
	}
std:printf("Sprite load done!\n");
}
void Animotion::LoadAnimations(const char* a_AnimationSheet)
{
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLNode *rootNode, *currentNode;
	tinyxml2::XMLElement *childElement, *child;
	std::string str, aniName;
	doc.LoadFile(a_AnimationSheet);
	rootNode = doc.FirstChildElement("animation");
	currentNode = rootNode;

	for (childElement = currentNode->ToElement();
		childElement != NULL; childElement = childElement->NextSiblingElement())
	{
		aniName = childElement->Attribute("name");
		int i = 0;
		for (child = childElement->FirstChildElement();
			child != NULL; child = child->NextSiblingElement())
		{
			str = child->Attribute("name");
			animotion[aniName].push_back(str);
			i++;
		}
	std:printf("Animation load done!\n");
	}
}
void Animotion::setAnimation(std::string animation, PlayType type)
{
	currentAnimotion = animation;
	currentFrame = 0;
	loopFrame = 0;
	currentPlayType = type;
	switch (type){
	case ONCE:
		break;
	case LOOP:
		loopFrame = 0;
		break;
	case LOOPSECTION:
		setAnimation(animation, type);
	case SINGLE:
		break;
	}
	currentSprite = animotion.at(currentAnimotion)[currentFrame];
	setSprite();
}
void Animotion::setAnimotion(std::string animation, PlayType type, int frame)
{
	switch (type)
	{
	case LOOPSECTION:
		currentAnimotion = animation;
		currentFrame = 0;
		currentPlayType = type;
		loopFrame = frame;
		break;
	default:
		setAnimation(animation, type);
		break;
	}
}
void Animotion::playAnimation()
{
		elapsedTime += getDeltaTime();

		if (elapsedTime > frames){
			elapsedTime = 0;
			switch (currentPlayType){
			case ONCE:
				if (animotion.at(currentAnimotion)[currentFrame] != animotion.at(currentAnimotion).back())
				{
					currentFrame++;
					currentSprite = animotion.at(currentAnimotion)[currentFrame];
				}
				break;
			case LOOPSECTION:
			case LOOP:
				if (animotion.at(currentAnimotion)[currentFrame] == animotion.at(currentAnimotion).back())
				{
					currentFrame = loopFrame;
					currentSprite = animotion.at(currentAnimotion)[currentFrame];
				}
				else
				{
					currentFrame++;
					currentSprite = animotion.at(currentAnimotion)[currentFrame];
				}
				break;
			case REVERSE:
				currentFrame = animotion[currentAnimotion].size();
				loopFrame = currentFrame;
				break;
			case SINGLE:
				break;
			default:
				break;
			}

			setSprite();
		}
}
unsigned int Animotion::CreateSprite(const char* a_fileName, int width, int height, unsigned int shader)
{
	Sprite s = Sprite(a_fileName, 0, 0, width, height);
	s.uiShaderProg = shader;
	SpriteList.emplace_back(s);

	return SpriteList.size() - 1;
}
void Animotion::DrawSprite()
{
	sprite->Draw();
}
void Animotion::MoveSprite(float x, float y)
{
	sprite->x = x;
	sprite->y = y;
}
double getDeltaTime()
{
	return deltaTime;
}
void resetDeltaTime()
{
	deltaTime = glfwGetTime();
	elapsedTime += deltaTime;
	frames++;
	if (elapsedTime > 1.25)
	{
		fps = (double)frames / elapsedTime;
		elapsedTime = 0;
		frames = 0;
	}
	glfwSetTime(0);
};