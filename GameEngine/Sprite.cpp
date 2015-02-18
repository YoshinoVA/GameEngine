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
	int imageWidth = 0;
	int imageHeight = 0;
	bpp = 4;
	spriteID = loadTexture(a_file, imageWidth, imageHeight, bpp);
	sWidth = width;
	sHeight = height;

	vertices[0].Position = glm::vec4(x - sWidth, y - sHeight, 0, 1);
	vertices[1].Position = glm::vec4(x - sWidth, y + sHeight, 0, 1);
	vertices[2].Position = glm::vec4(x + sWidth, y + sHeight, 0, 1);
	vertices[3].Position = glm::vec4(x + sWidth, y - sHeight, 0, 1);
	vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color = glm::vec4(1, 1, 1, 1);
	vertices[0].uv = glm::vec2(0, 0);
	vertices[1].uv = glm::vec2(0, 1);
	vertices[2].uv = glm::vec2(1, 1);
	vertices[3].uv = glm::vec2(1, 0);

	glGenBuffers(1, &uiVBO);
	glGenBuffers(1, &uiIBO);
}

void Sprite::UpdateUV(glm::vec2 vOne, glm::vec2 vTwo, glm::vec2 vThree, glm::vec2 vFour)
{
	vertices[0].uv = vOne;
	vertices[1].uv = vTwo;
	vertices[2].uv = vThree;
	vertices[3].uv = vFour;
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

		memcpy(vSBuffer, vertices, sizeof(vertex)* 4);

		glUnmapBuffer(GL_ARRAY_BUFFER);
	}

	glBindTexture(GL_TEXTURE_2D, spriteID);
	glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiVBO);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(sizeof(float)* 4));

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(sizeof(float)* 8));

	glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_BYTE, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}