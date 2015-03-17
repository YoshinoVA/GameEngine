#define GLEW_STATIC

#include "glew/glew.h"
#include "GLFW/glfw3.h"
#include "soil/soil.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Sprite.h"
#include "Animotion.h"
#include <fstream>
#include <iostream>
#include <ctime>

//vertex shader
const GLchar* vertexSource =
"#version 150 core\n"
"in vec4 position;"
"in vec4 color;"
"in vec2 texcoord;"
"uniform mat4 mvp_matrix;"
"out vec4 Color;"
"out vec2 Texcoord;"
"void main() {"
"   Color = color;"
"   Texcoord = texcoord;"
"   gl_Position = mvp_matrix * position;"
//"   gl_Position = position;"
"}";
const GLchar* fragmentSource =
"#version 150 core\n"
"in vec4 Color;"
"in vec2 Texcoord;"
"out vec4 outColor;"
"uniform sampler2D tex;"
"void main() {"
"   outColor = texture(tex, Texcoord) * Color;"
"}";

static bool printShaderInfoLog(GLuint obj)
{
	int infologLength = 0;
	int charsWritten = 0;
	char *infoLog;

	glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n", infoLog);
		free(infoLog);
		return false;
	}
	else
	{
		printf("Info log was empty\n");
	}
	return true;
}

int main()
{
	glfwInit();

	int screenWidth = 1024;
	int screenHeight = 720;

	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, ":3", nullptr, nullptr);

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit() != GLEW_OK;

	//compile shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	// get debugging info for shaders
	printShaderInfoLog(vertexShader);
	printShaderInfoLog(fragmentShader);

	// compile shaderprogram
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	//gameworks
	/*Sprite* s = new Sprite();
	s->uiShaderProg = shaderProgram;
	s->LoadTexture("ice.png");*/

	Sprite* c = new Sprite("MegamanXSheet.png", 0, 0, 56, 56);
	c->uiShaderProg = shaderProgram;
	//c->LoadTexture("cirno walk.png");

	Animotion* q = new Animotion();
	q->sprite = c;
	c->aniMate = q;
	c->LoadTexture("MegamanXSheet.png");
	c->aniMate->ImportSheet("MegamanXSheet.xml");
	c->aniMate->setAnimation("run", LOOP);
	//q->spriteID = q->CreateSprite("cirno walk.png", 406, 58, shaderProgram);

	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);

		// Clear the screen to black
		glClearColor(0.1f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw a bunch of rocks and shit
		glUseProgram(shaderProgram);
		//c->Draw();
		q->MoveSprite(screenWidth / 2, screenHeight / 2);
		q->DrawSprite();
		
		c->aniMate->playAnimation();
		//s->Draw();
		
		glfwPollEvents();
		resetDeltaTime();
	}
	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	glfwTerminate();

	return 0;
} 