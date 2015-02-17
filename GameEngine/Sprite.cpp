#include "Sprite.h"


unsigned int Sprite::loadTexture(const char* a_file, int & a_Width, int & a_Height, int & a_BPP)
{
	unsigned int uiTextureID = 0;

	if (a_file != nullptr)
	{
		unsigned char* imageData = SOIL_load_image(a_file, &a_Width, &a_Height, &a_BPP, SOIL_LOAD_AUTO);

		if (imageData)
		{
			uiTextureID = SOIL_create_OGL_texture(imageData, a_Width, a_Height, a_BPP, SOIL_LOAD_RGB,
				SOIL_CREATE_NEW_ID);
			SOIL_free_image_data(imageData);
		}
		if (uiTextureID == 0)
		{

		}
		return uiTextureID;
	}
}

Sprite::Sprite(const char* a_file, float a_loc[2], int a_size[2], int a_BPP)
{
	int imageWidth = 0;
	int imageHeight = 0;
	int bpp = 4;
	spriteID = loadTexture(a_file, imageWidth, imageHeight, bpp);

	// loading UV data like 4 times
	vertices[0].UVx = 0.f, vertices[0].UVy = .5f, vertices[0].UVz = .16f, vertices[0].UVw = 1.f;
	vertices[1].UVx = 0.f, vertices[1].UVy = .5f, vertices[1].UVz = .16f, vertices[1].UVw = 1.f;
	vertices[2].UVx = 0.f, vertices[2].UVy = .5f, vertices[2].UVz = .16f, vertices[2].UVw = 1.f;
	vertices[3].UVx = 0.f, vertices[3].UVy = .5f, vertices[3].UVz = .16f, vertices[3].UVw = 1.f;

	//the most obnoxious loading of all time
	Sprite::UVlist.push_back(glm::vec2(vertices[0].UVx, vertices[0].UVy));
	Sprite::UVlist.emplace_back(glm::vec2(vertices[0].UVx, vertices[0].UVw));
	Sprite::UVlist.emplace_back(glm::vec2(vertices[0].UVz, vertices[0].UVw));
	Sprite::UVlist.emplace_back(glm::vec2(vertices[0].UVz, vertices[0].UVy));

	Sprite::UVlist.push_back(glm::vec2(vertices[1].UVx, vertices[1].UVy));
	Sprite::UVlist.emplace_back(glm::vec2(vertices[1].UVx, vertices[1].UVw));
	Sprite::UVlist.emplace_back(glm::vec2(vertices[1].UVz, vertices[1].UVw));
	Sprite::UVlist.emplace_back(glm::vec2(vertices[1].UVz, vertices[1].UVy));

	Sprite::UVlist.push_back(glm::vec2(vertices[2].UVx, vertices[2].UVy));
	Sprite::UVlist.emplace_back(glm::vec2(vertices[2].UVx, vertices[2].UVw));
	Sprite::UVlist.emplace_back(glm::vec2(vertices[2].UVz, vertices[2].UVw));
	Sprite::UVlist.emplace_back(glm::vec2(vertices[2].UVz, vertices[2].UVy));

	Sprite::UVlist.push_back(glm::vec2(vertices[3].UVx, vertices[3].UVy));
	Sprite::UVlist.emplace_back(glm::vec2(vertices[3].UVx, vertices[3].UVw));
	Sprite::UVlist.emplace_back(glm::vec2(vertices[3].UVz, vertices[3].UVw));
	Sprite::UVlist.emplace_back(glm::vec2(vertices[3].UVz, vertices[3].UVy));

	// loc, size arrays, vertex 1
	vertices[0].PosX = a_loc[0] - a_size[0] * .5f;
	vertices[0].PosY = a_loc[1] - a_size[1] * .5f;
	vertices[0].uv[0] = vertices[0].UVx;
	vertices[0].uv[1] = vertices[0].UVy;

	//vertex 2
	vertices[1].PosX = a_loc[0] - a_size[0] * .5f;
	vertices[1].PosY = a_loc[1] - a_size[1] * .5f;
	vertices[1].uv[0] = vertices[1].UVx;
	vertices[1].uv[1] = vertices[1].UVy;

	//vertex 3
	vertices[2].PosX = a_loc[0] - a_size[0] * .5f;
	vertices[2].PosY = a_loc[1] - a_size[1] * .5f;
	vertices[2].uv[0] = vertices[2].UVx;
	vertices[2].uv[1] = vertices[2].UVy;

	//vertex 4
	vertices[3].PosX = a_loc[0] - a_size[0] * .5f;
	vertices[3].PosY = a_loc[1] - a_size[1] * .5f;
	vertices[3].uv[0] = vertices[3].UVx;
	vertices[3].uv[1] = vertices[3].UVy;

	for (int i = 0; i < 4; i++)
	{
		vertices[i].PosX = 0.0f;
		vertices[i].PosY = 1.0f;
		vertices[1].color[0] = 1.f;
		vertices[1].color[1] = 1.f;
		vertices[1].color[2] = 1.f;
		vertices[1].color[3] = 1.f;
	}
	glGenBuffers(1, &uiVBO);
	glGenBuffers(1, &uiIBO);
}