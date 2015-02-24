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
Sprite::Sprite(const char* a_file, int width, int height)
{
	int imageWidth = 50;
	int imageHeight = 54;
	vertex vertices[4];
	bpp = 4;
	spriteID = loadTexture(a_file, imageWidth, imageHeight, bpp);
	sWidth = imageWidth;
	sHeight = imageHeight;

	vertices[0].Position = (x - sWidth, y - sHeight, 0, 0);
	vertices[1].Position = (x - sWidth, y + sHeight, 0, 1);
	vertices[2].Position = (x + sWidth, y + sHeight, 1, 1);
	vertices[3].Position = (x + sWidth, y - sHeight, 1, 0);
	vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color = (1.0, 1.0, 1.0, 1.0);
	vertices[0].uv = (0, 0);
	vertices[1].uv = (1, 1);

	glGenBuffers(1, &uiVBO);
	glGenBuffers(1, &uiIBO);
}
void Sprite::Draw()
{
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_ALPHA);
	glFrontFace(GL_CW);

	if (uiIBO != 0);
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(char), NULL, GL_STATIC_DRAW);
		GLvoid* iBuffer = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);

		for (int i = 0; i < 4; i++)
		{
			((char*)iBuffer)[i] = i;
		}
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	if (uiVBO != 0)
	{
		glBindBuffer(GL_ARRAY_BUFFER, uiVBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex)* 4, NULL, GL_STATIC_DRAW);

		GLvoid* vSBuffer = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

		glUnmapBuffer(GL_ARRAY_BUFFER);
	}

	glBindTexture(GL_TEXTURE_2D, spriteID);
	glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiVBO);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(sizeof(float)* 4));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(sizeof(float)* 8));

	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
Sprite::Sprite()
{

}
Sprite::~Sprite()
{

}