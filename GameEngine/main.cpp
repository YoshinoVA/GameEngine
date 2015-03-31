#define GLEW_STATIC

#include "glew/glew.h"
#include "GLFW/glfw3.h"
#include "soil/soil.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Sprite.h"
#include "Animotion.h"
#include "Graph.h"
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

	int screenWidth = 1080;
	int screenHeight = 800;

	GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "I'm really feeling it", nullptr, nullptr);

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

	//Nodes
	Graph graph;
	GraphNode graphThings;
	
	//std::cout << graph.returnPath() << std::endl;

	graph.generateNodes(10, 10);

	bool result = graph.searchDFS(graph.Node[1], graph.Node[99]);
	std::vector<GraphNode *> path = graph.returnPath();


	std::cout << "--PATH--\n";
	for (int i = 0; i < path.size(); i++)
	{
		std::cout << path[i]->a_NodeNum << "\n";
	}

	graph.sprite = new Sprite("gridtiles\\tile1.png", 100, 100, 64, 64);
	graph.visitedSprite = new Sprite("gridtiles\\visitedTile.png", 100, 100, 64, 64);
	graph.player = new Sprite("player.png", 5, 3, 34, 58);
	graph.sprite->uiShaderProg = shaderProgram;
	graph.visitedSprite->uiShaderProg = shaderProgram;
	graph.player->uiShaderProg = shaderProgram;

	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);

		// Clear the screen to black
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		graph.drawNodes();

		for (int i = 0; i < path.size(); i++)
		{
			graph.player->x = path[i]->x;
			graph.player->y = path[i]->y;
			graph.player->Draw();
		}

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