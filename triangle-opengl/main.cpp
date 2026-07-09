#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

namespace
{
	std::string vertexShader = "#version 430\n"
		"in vec3 pos;"
		"void main() {"
		"gl_Position = vec4(pos, 1);"
		"}";

	std::string fragmentShader = "#version 430\n"
		"void main() {"
		"gl_FragColor = vec4(1, 0, 0, 1);"
		"}";

	GLuint compileShaders(const std::string& shader, GLenum type)
	{
		const char* shaderCode = shader.c_str();
		GLuint shaderId = glCreateShader(type);
		if (!shaderId)
		{
			throw std::logic_error("Error creating shader");
		}

		glShaderSource(shaderId, 1, &shaderCode, nullptr);
		glCompileShader(shaderId);

		GLint compileStatus;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compileStatus);
		if (!compileStatus)
		{
			int length;
			glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &length);
			
			std::string strMessage(length, 'a');
			char* cMessage = const_cast< char* >(strMessage.c_str());

			glGetShaderInfoLog(shaderId, length, &length, cMessage);
			strMessage = cMessage;

			glDeleteShader(shaderId);

			throw std::logic_error("Cannot compile shader: " + strMessage);
		}
		return shaderId;
	}

	GLuint linkProgram(GLuint vertexShaderId, GLuint fragmentShaderId)
	{
		GLuint programId = glCreateProgram();
		if (!programId)
		{
			throw std::logic_error("Error creating shader program");
		}
		glAttachShader(programId, vertexShaderId);
		glAttachShader(programId, fragmentShaderId);

		glLinkProgram(programId);

		GLint linkStatus;

		glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus);
		if (!linkStatus)
		{
			glDetachShader(programId, vertexShaderId);
			glDetachShader(programId, fragmentShaderId);
			glDeleteProgram(programId);

			throw std::logic_error("Error linking program");
		}
		return programId;
	}

	GLuint loadDataInBuffers()
	{
		GLfloat vertices[]{
			-0.7, -0.7, 0,
			0.7, -0.7, 0,
			0, 0.7, 0
		};

		GLuint vboID;

		glGenBuffers(1, &vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		return vboID;
	}

	void init()
	{
		glClearColor(0, 0, 0, 0);

		GLuint vboId = loadDataInBuffers();

		GLuint vShaderId = compileShaders(vertexShader, GL_VERTEX_SHADER);
		GLuint fShaderId = compileShaders(fragmentShader, GL_FRAGMENT_SHADER);

		GLuint programId = linkProgram(vShaderId, fShaderId);

		GLuint posAttributePosition = glGetAttribLocation(programId, "pos");

		GLuint vaoId;
		glGenVertexArrays(1, &vaoId);

		glBindVertexArray(vaoId);

		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glVertexAttribPointer(posAttributePosition, 3, GL_FLOAT, false, 0, 0);

		glEnableVertexAttribArray(posAttributePosition);

		glUseProgram(programId);
	}
}

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewInit();
	init();

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

