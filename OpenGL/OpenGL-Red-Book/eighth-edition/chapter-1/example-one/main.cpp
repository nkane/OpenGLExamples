#include <iostream>

#define GLEW_STATIC

#include "glew.h"
#include "glfw3.h"

#define BUFFER_OFFSET(a) ((void *)(a))

void init(void);
void display(void);
static const GLchar* ReadShader(const char *);

enum VAO_IDs
{
	Triangles = 0,
	NumVAOs = 1,
};

enum Buffer_IDs 
{
	ArrayBuffer = 0,
	NumBuffers = 1,
};

enum Attrib_IDs
{
	vPosition = 0,
};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];

const GLuint NumVertices = 6;

int main(int argc, char *argv[])
{
	GLFWwindow *window;

	if (!glfwInit())
	{
		return -1;
	}

	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit())
	{
		glfwTerminate();
		return -1;
	}

	init();

	while (!glfwWindowShouldClose(window))
	{
		display();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	
	glfwTerminate();

	return 0;
}

void init(void)
{
	glGenVertexArrays(NumVAOs, VAOs);
	glBindVertexArray(VAOs[Triangles]);

	GLfloat vertices[NumVertices][2] =
	{
		// Triangle One
		{ -0.90f, -0.90f },
		{  0.85f, -0.90f }, 
		{ -0.90f,  0.85f },
		// Triangle Two
		{  0.90f, -0.80f },
		{  0.90f,  0.90f },
		{ -0.85f,  0.90f }
	};

	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint GLProgram = glCreateProgram();

	// NOTE(nick): vertex shader
	GLuint Vertex_Shader = glCreateShader(GL_VERTEX_SHADER);
	const GLchar *source = ReadShader(".\\triangles.vert");

	glShaderSource(Vertex_Shader, 1, &source, NULL); 

	glCompileShader(Vertex_Shader);

	GLint compiled;

	glGetShaderiv(Vertex_Shader, GL_COMPILE_STATUS, &compiled);

	if (!compiled)
	{
		GLsizei len;
		glGetShaderiv(Vertex_Shader, GL_INFO_LOG_LENGTH, &len);

		GLchar *log = new GLchar[len + 1];
		glGetShaderInfoLog(Vertex_Shader, len, &len, log);

		std::cerr << log << std::endl;

		delete [] log;
	}

	glAttachShader(GLProgram, Vertex_Shader);

	// NOTE(nick): fragment shader
	GLuint Fragment_Shader = glCreateShader(GL_FRAGMENT_SHADER);
	source = ReadShader(".\\triangles.frag");

	glShaderSource(Fragment_Shader, 1, &source, NULL); 

	glCompileShader(Fragment_Shader);

	glGetShaderiv(Fragment_Shader, GL_COMPILE_STATUS, &compiled);

	if (!compiled)
	{
		GLsizei len;
		glGetShaderiv(Fragment_Shader, GL_INFO_LOG_LENGTH, &len);

		GLchar *log = new GLchar[len + 1];
		glGetShaderInfoLog(Fragment_Shader, len, &len, log);

		std::cerr << log << std::endl;

		delete [] log;
	}

	glAttachShader(GLProgram, Fragment_Shader);

	glLinkProgram(GLProgram);

	GLint linked;

	glGetProgramiv(GLProgram, GL_LINK_STATUS, &linked);

	if (!linked)
	{
	        GLsizei len;
	        glGetProgramiv(GLProgram, GL_INFO_LOG_LENGTH, &len);

	        GLchar* log = new GLchar[len + 1];
        	glGetProgramInfoLog(GLProgram, len, &len, log);

		std::cerr << log << std::endl;

        	delete [] log;
	}

	delete [] source;

	glUseProgram(GLProgram);
	
	glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(vPosition);
}

void display(void)
{
	static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };

	glClearBufferfv(GL_COLOR, 0, black);

	glBindVertexArray(VAOs[Triangles]);
	glDrawArrays(GL_TRIANGLES, 0, NumVertices);
}

static const GLchar* ReadShader(const char *filename)
{
	FILE *InFile;
	fopen_s(&InFile, filename, "rb");

	if (!InFile) 
	{
		std::cerr << filename << std::endl;
	}

	fseek(InFile, 0, SEEK_END);
	int len = ftell(InFile);
	fseek(InFile, 0, SEEK_SET);

	GLchar *source = new GLchar[len + 1];

	fread(source, 1, len, InFile);
	fclose(InFile);

	source[len] = 0;

	return const_cast<const GLchar *>(source);
}

