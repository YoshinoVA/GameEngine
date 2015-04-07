#include "Sprite.h"

#include "MathStuffandShit.h"
#include <glm\glm.hpp>

#include "graph.h"


Sprite::Sprite(const char* a_file, float xPos, float yPos, float newWidth, float newHeight)
{
	x = xPos;
	y = yPos;
	width = newWidth;
	height = newHeight;

	printf("That's a sprite, I think\n");

	// vertex 1 - top left
	vertices[0].Position[0] = x;
	vertices[0].Position[1] = y;
	vertices[0].Position[2] = 0.0f;
	vertices[0].Position[3] = 1.0f;
	vertices[0].color[0] = 1.0f;
	vertices[0].color[1] = 1.0f;
	vertices[0].color[2] = 1.0f;
	vertices[0].color[3] = 1.0f;
	vertices[0].uv[0] = 0.0f;
	vertices[0].uv[1] = 0.0f;

	//vertex 2 - top right
	vertices[1].Position[0] = x + width;
	vertices[1].Position[1] = y;
	vertices[1].Position[2] = 0.0f;
	vertices[1].Position[3] = 1.0f;
	vertices[1].color[0] = 1.0f;
	vertices[1].color[1] = 1.0f;
	vertices[1].color[2] = 1.0f;
	vertices[1].color[3] = 1.0f;
	vertices[1].uv[0] = 1.0f;
	vertices[1].uv[1] = 0.0f;

	//vertex 3 - bottom right
	vertices[2].Position[0] = x + width;
	vertices[2].Position[1] = y + height;
	vertices[2].Position[2] = 0.0f;
	vertices[2].Position[3] = 1.0f;
	vertices[2].color[0] = 1.0f;
	vertices[2].color[1] = 1.0f;
	vertices[2].color[2] = 1.0f;
	vertices[2].color[3] = 1.0f;
	vertices[2].uv[0] = 1.0f;
	vertices[2].uv[1] = 1.0f;

	//vertex  - bottom left
	vertices[3].Position[0] = x;
	vertices[3].Position[1] = y + height;
	vertices[3].Position[2] = 0.0f;
	vertices[3].Position[3] = 1.0f;
	vertices[3].color[0] = 1.0f;
	vertices[3].color[1] = 1.0f;
	vertices[3].color[2] = 1.0f;
	vertices[3].color[3] = 1.0f;
	vertices[3].uv[0] = 0.0f;
	vertices[3].uv[1] = 1.0f;

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

	spriteID = LoadTexture(a_file);
}
void Sprite::Draw()
{
	vertices[0].Position[0] = x;
	vertices[0].Position[1] = y;

	vertices[1].Position[0] = x + width;
	vertices[1].Position[1] = y;

	vertices[2].Position[0] = x + width;
	vertices[2].Position[1] = y + height;

	vertices[3].Position[0] = x;
	vertices[3].Position[1] = y + height;

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);

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

	glm::mat4 mvp;
	MathStuff::getOrtho(0, 1024, 720, 0, -1, 1, mvp);

	GLint mvpAttrib = glGetUniformLocation(uiShaderProg, "mvp_matrix");
	glUniformMatrix4fv(mvpAttrib, 1, GL_FALSE, glm::value_ptr(mvp));

	glVertexAttribPointer(posAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), 0);
	glVertexAttribPointer(colAttrib, 4, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(sizeof(float)* 4));
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(sizeof(float)* 8));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_2D, TexThing);

	glUniform1i(texLocation, 0);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
unsigned int Sprite::LoadTexture(const char* a_Texture)
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

	unsigned int uiTextureID = 0;
	//check file exists
	if (a_Texture != nullptr)
	{
		//read in image data from file
		unsigned char* pImageData = SOIL_load_image(a_Texture, &width, &height, 0, SOIL_LOAD_RGBA);

		//check for successful read
		if (pImageData)
		{
			unsigned char* image = SOIL_load_image(a_Texture, &width, &height, 0, SOIL_LOAD_RGBA);
			glBindTexture(GL_TEXTURE_2D, TexThing);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			SOIL_free_image_data(image);
		}

		//check for errors
		if (uiTextureID == 0)
		{
			std::cerr << "SOIL loading error: " << SOIL_last_result() << std::endl;
		}
		return uiTextureID;
	}
}
Sprite::Sprite()
{

}
Sprite::~Sprite()
{
	printf("Mother of all that is holy...\n");
}
void Tank::Update()
{
	// changes our position based on velocity
	x += Velocity.x * getDeltaTime();
	y += Velocity.y * getDeltaTime();

	float dist = glm::distance(glm::vec2(path[currentIndex]->x, path[currentIndex]->y), glm::vec2(x, y));

	//std::cout << "Dist: " << dist << "\n";

	// check to see if we are close enough to the node we're trying to move to
	if(dist  < 100.f)
	{
		if (currentIndex+1 < path.size())
		{
			currentIndex += 1;
		}
	}
	// if we're close enough, switch targets to the next node
}
void Tank::Seek()
{
	// set our velocity to point towards the node we want to go to
	Velocity = glm::normalize(glm::vec2(path[currentIndex]->x, path[currentIndex]->y) - glm::vec2(x,y)) * maxVelocity;
}
Tank::Tank(const char* a_file, float xPos, float yPos, float newWidth, float newHeight) : Sprite(a_file, xPos,yPos,newWidth,newHeight)
{

}
Tank::Tank()
{

}
Tank::~Tank()
{

}
void SteerBehav::Update()
{
	x += Velocity.x * getDeltaTime();
	y += Velocity.y * getDeltaTime();

	float dist = glm::distance(glm::vec2(target->x, target->y), glm::vec2(x, y));

	if (dist < 100.f)
	{
		if (target->x, target->y != x, y)
		{
			
		}
	}
}
void SteerBehav::Seek2()
{
	Velocity = glm::normalize(glm::vec2(target->x, target->y) - (glm::vec2(x, y))) * maxVelocity;
}
void SteerBehav::Flee()
{
	Velocity = glm::normalize((glm::vec2(x, y)) - (glm::vec2(target->x, target->y))) * maxVelocity;
}
void SteerBehav::Arrive()
{
	Velocity = truncate(Velocity, maxVelocity);
	glm::vec2(x, y) = glm::vec2(x, y) + Velocity;

	Velocity = glm::vec2(x, y) - glm::vec2(target->x, target->y);
	distance = glm::distance(glm::vec2(x, y), glm::vec2(target->x, target->y));

	if (distance < slowingRadius)
	{
		Velocity = glm::normalize(Velocity) * maxVelocity * (distance / slowingRadius);
	}
	else
	{
		Velocity = normalize(Velocity) * maxVelocity;
	}

	Velocity *= -1;
}
glm::vec2 SteerBehav::truncate(glm::vec2 vector, float number)
{
	float i;
	i = number / vector.length();
	i = i < 1.0 ? i : 1.0;
	vector = vector * i;

	return vector;
}
void SteerBehav::Wander()
{

}
SteerBehav::SteerBehav(const char* a_file, float xPos, float yPos, float newWidth, float newHeight) : Sprite(a_file, xPos, yPos, newWidth, newHeight)
{

}
SteerBehav::SteerBehav()
{

}
SteerBehav::~SteerBehav()
{

}