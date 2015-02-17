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

Sprite::Sprite(const char* a_file, int a_BPP)
{
	int imageWidth = 0;
	int imageHeight = 0;
	int bpp = 4;
	spriteID = loadTexture(a_file, imageWidth, imageHeight, bpp);

	// loc, size arrays
	vertices[0].PosX = 0;
}