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

void Animotion::playAnimation(AnimationType desiredState)
{
	AnimatingSpriteMap[desiredState].UpdateUV(MappedFrames[desiredState][0].One_uv,
		MappedFrames[desiredState][0].Two_uv,
		MappedFrames[desiredState][0].Three_uv,
		MappedFrames[desiredState][0].Four_uv);
		AnimatingSpriteMap[desiredState].Draw();
}