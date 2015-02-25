#include "animotion.h"

void Animotion::dumptostdout(const char* a_File)
{
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
void Animotion::loadAnimotionUV(const char* a_File, AnimationType currentState)
{
	dumptostdout(a_File);
	docAtlas = doc.FirstChildElement();
	firstElement = docAtlas->FirstChildElement();
	frame Temp;

	for (siblingElement = firstElement; siblingElement != nullptr; siblingElement = siblingElement->NextSiblingElement())
	{
		int x, y, width, height;
		width = siblingElement->IntAttribute("width");
		height = siblingElement->IntAttribute("height");

		//Vert 1
		x = siblingElement->IntAttribute("x");
		y = siblingElement->IntAttribute("y") - height;
		Temp.One_uv = glm::vec2(x, y);

		//Vert 2
		x = siblingElement->IntAttribute("x");
		Temp.Two_uv = glm::vec2(x, y);

		//Vert 3
		x = siblingElement->IntAttribute("x") + width;
		y = siblingElement->IntAttribute("y");
		Temp.Three_uv = glm::vec2(x, y);

		//Vert 4
		x = siblingElement->IntAttribute("x") + width;
		y = siblingElement->IntAttribute("y") - height;
		Temp.Four_uv = glm::vec2(x, y);

		FramesAnimated.emplace_back(Temp);
		Temp.frameNumber++;
	}
	MappedFrames.emplace(std::pair<AnimationType, std::vector<frame>>(currentState, FramesAnimated));
}
unsigned int Animotion::CreateSprite(const char* a_fileName, int width, int height, unsigned int shader)
{

	Sprite s = Sprite(a_fileName, width, height);
	s.uiShaderProg = shader;
	SpriteList.push_back(s);

	return SpriteList.size() - 1;

}
void Animotion::DrawSprite(unsigned int s)
{
	SpriteList[s].Draw();
}
void Animotion::MoveSprite(unsigned int s, float x, float y)
{
	SpriteList[s].x = x;
	SpriteList[s].y = y;
	UpdateVertex(s);
}
void Animotion::UpdateVertex(unsigned int s)
{

}


//void Animotion::playAnimation(AnimationType desiredState)
//{
//
//}