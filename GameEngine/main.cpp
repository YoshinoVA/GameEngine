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
"out vec3 Color;"
"out vec2 Texcoord;"
"void main() {"
"   Color = color;"
"   Texcoord = texcoord;"
"   gl_Position = vec4(0.0, 0.0, 0.0, 1.0);"
"}";
const GLchar* fragmentSource =
"#version 150 core\n"
"in vec3 Color;"
"in vec2 Texcoord;"
"out vec4 outColor;"
"uniform sampler2D tex;"
"void main() {"
"   outColor = texture(tex, Texcoord) * vec4(Color, 1.0);"
"	outColor = vec4(1.0,1.0,1.0,1.0);"
"}";

//test shaders
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
	return true;
}
float radianToDegrees(float radians)
{
	float returnNumber;

	// degrees to radian
	returnNumber = radians * 180 / 3.14;

	return returnNumber;
}
unsigned int Animotion::CreateSprite(const char* a_fileName, int width, int height)
{
	Sprite s(a_fileName, width, height);
	SpriteList.emplace_back(s);
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
	SpriteList[s].vertices[0].Position = glm::vec4(SpriteList[s].x - SpriteList[s].sWidth, SpriteList[s].y - SpriteList[s].sHeight, 0, 1);
	SpriteList[s].vertices[1].Position = glm::vec4(SpriteList[s].x - SpriteList[s].sWidth, SpriteList[s].y + SpriteList[s].sHeight, 0, 1);
	SpriteList[s].vertices[2].Position = glm::vec4(SpriteList[s].x + SpriteList[s].sWidth, SpriteList[s].y + SpriteList[s].sHeight, 0, 1);
	SpriteList[s].vertices[3].Position = glm::vec4(SpriteList[s].x + SpriteList[s].sWidth, SpriteList[s].y - SpriteList[s].sHeight, 0, 1);
}

Animotion Engine;

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(1024, 720, "I'm really feeling it", nullptr, nullptr);
	//GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", glfwGetPrimaryMonitor(), nullptr);

	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	float x, y;
	x = y = 400;
	float speed = 250.f;

	unsigned int r = Engine.CreateSprite("rock.png", 50, 54);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);

	// math and numbers and stuff
	GLfloat vertices[] = {
		//  Position   Color             Texcoords
		-0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, // Top-left
		0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // Top-right
		0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // Bottom-right
		-0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f  // Bottom-left
	};

	GLuint ebo;
	glGenBuffers(1, &ebo);

	GLuint elements[] = {
		0, 1, 2,
		2, 3, 0
	};

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//compile shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);

	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), 0);

	GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2 * sizeof(float)));

	GLint texAttrib = glGetAttribLocation(shaderProgram, "texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	GLuint tex;
	glGenTextures(1, &tex);

	int width, height;
	unsigned char* image = SOIL_load_image("Western Air Temple.png", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	printShaderInfoLog(vertexShader);
	printShaderInfoLog(fragmentShader);

	int infologLength = 0;
	int charsWritten = 0;
	char *infoLog;
	glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infologLength);
	if (infologLength > 0)
	{
		infoLog = (char *)malloc(infologLength);
		glGetProgramInfoLog(shaderProgram, infologLength, &charsWritten, infoLog);
		printf("%s\n", infoLog);

		free(infoLog);
	}
	else
	{
		printf("djhkfgal");
	}

	while (!glfwWindowShouldClose(window))
	{
		// Clear the screen to black
		glClearColor(0.1f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw a bunch of rocks and shit
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glUseProgram(shaderProgram);
		Engine.MoveSprite(r, x, y);
		Engine.DrawSprite(r);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteProgram(shaderProgram);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);

	glDeleteBuffers(1, &ebo);
	glDeleteBuffers(1, &vbo);

	glDeleteVertexArrays(1, &vao);


	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	glfwTerminate();

	return 0;
} 