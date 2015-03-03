#include "Sprite.h"


Sprite::Sprite(const char* a_file, int width, int height) : Sprite()
{

}
void Sprite::Draw()
{
	// vertex 1
	vertices[0].Position[0] = -0.5f;
	vertices[0].Position[1] = 0.5f;
	vertices[0].Position[2] = 0.0f;
	vertices[0].Position[3] = 1.0f;
	vertices[0].color[0] = 1.0f;
	vertices[0].color[1] = 1.0f;
	vertices[0].color[2] = 1.0f;
	vertices[0].color[3] = 1.0f;
	vertices[0].uv[0] = 0.0f;
	vertices[0].uv[1] = 0.0f;

	//vertex 2
	vertices[1].Position[0] = 0.5f;
	vertices[1].Position[1] = 0.5;
	vertices[1].Position[2] = 0.0f;
	vertices[1].Position[3] = 1.0f;
	vertices[1].color[0] = 1.0f;
	vertices[1].color[1] = 1.0f;
	vertices[1].color[2] = 1.0f;
	vertices[1].color[3] = 1.0f;
	vertices[1].uv[0] = 1.0f;
	vertices[1].uv[1] = 0.0f;

	//vertex 3
	vertices[2].Position[0] = 0.5f;
	vertices[2].Position[1] = -0.5f;
	vertices[2].Position[2] = 0.0f;
	vertices[2].Position[3] = 1.0f;
	vertices[2].color[0] = 1.0f;
	vertices[2].color[1] = 1.0f;
	vertices[2].color[2] = 1.0f;
	vertices[2].color[3] = 1.0f;
	vertices[2].uv[0] = 1.0f;
	vertices[2].uv[1] = 1.0f;

	//vertex 4
	vertices[3].Position[0] = -0.5f;
	vertices[3].Position[1] = -0.5f;
	vertices[3].Position[2] = 0.0f;
	vertices[3].Position[3] = 1.0f;
	vertices[3].color[0] = 1.0f;
	vertices[3].color[1] = 1.0f;
	vertices[3].color[2] = 1.0f;
	vertices[3].color[3] = 1.0f;
	vertices[3].uv[0] = 0.0f;
	vertices[3].uv[1] = 1.0f;

	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);

	glGenBuffers(1, &uiVBO);
	glGenBuffers(1, &uiIBO);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	glGenVertexArrays(1, &uiVAO);
	glBindVertexArray(uiVAO);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIBO);
	glBindVertexArray(uiVAO);
	glBindTexture(GL_TEXTURE_2D, spriteID);

	GLint posAttrib = glGetAttribLocation(uiShaderProg, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE,sizeof(vertex), 0);

	GLint colAttrib = glGetAttribLocation(uiShaderProg, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(4 * sizeof(float)));

	GLint texAttrib = glGetAttribLocation(uiShaderProg, "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(8 * sizeof(float)));

	glVertexAttribPointer(posAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
	glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(sizeof(float)* 4));
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(sizeof(float)* 8));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_2D, TexThing);

	glUniform1i(texLocation, 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
void Sprite::LoadTexture(const char* a_Texture)
{
	TexThing = 0;

	glGenTextures(1, &TexThing);
	glActiveTexture(GL_TEXTURE0);

	int width, height;
	unsigned char* image = SOIL_load_image(a_Texture, &width, &height, 0, SOIL_LOAD_RGBA);
	glBindTexture(GL_TEXTURE_2D, TexThing);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	texLocation = glGetUniformLocation(uiShaderProg, "difTex");
}
Sprite::Sprite()
{
	printf("That's a sprite, I think\n");
}
Sprite::~Sprite()
{
	printf("Mother of all that is holy...\n");
}