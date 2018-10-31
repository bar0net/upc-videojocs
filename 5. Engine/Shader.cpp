#include "Shader.h"

#include <vector>

#include "GL/glew.h"
#include "Globals.h"

Shader::Shader(const char * vShaderFile, const char * fShaderFile)
{
	unsigned int vShader = CompileShader(vShaderFile, (int)GL_VERTEX_SHADER);
	unsigned int fShader = CompileShader(fShaderFile, (int)GL_FRAGMENT_SHADER);

	if (valid)
	{
		program = glCreateProgram();
		glAttachShader(program, vShader);
		glAttachShader(program, fShader);
		glLinkProgram(program);

		int success = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &success);

		if (success == GL_FALSE)
		{
			LOG("Program failed to link: %s & %s", vShaderFile, fShaderFile);
		}
		else LOG("Program successfully linked: %s & %s", vShaderFile, fShaderFile);
	}

	glDetachShader(program, vShader);
	glDetachShader(program, fShader);

	if (vShader != 0) glDeleteShader(vShader);
	if (fShader != 0) glDeleteShader(fShader);

	// Set Unifrom Block Index to binding point 0
	unsigned int index = glGetUniformBlockIndex(program, "GlobalMatrices");
	glUniformBlockBinding(program, index, 0);
}

Shader::~Shader()
{
	glDeleteProgram(program);
}

void Shader::Bind() const
{
	glUseProgram(program);
}

void Shader::UnBind() const
{
	glUseProgram(0);
}

char * Shader::ReadFile(const char * filename)
{
	char* data = nullptr;
	FILE* file = nullptr;
	fopen_s(&file, filename, "rb");

	if (file)
	{
		fseek(file, 0, SEEK_END);
		int size = ftell(file);
		rewind(file);
		data = (char*)malloc(size + 1);

		fread(data, 1, size, file);
		data[size] = 0;

		fclose(file);
	}
	else LOG("File not found: %s", filename);

	return data;
}

unsigned int Shader::CompileShader(const char * filename, int type)
{
	int success = 0;

	char* shaderData = ReadFile(filename);
	if (shaderData == nullptr)
	{
		LOG("Could not load %s", filename);
		return 0;
	}

	unsigned shader = glCreateShader((GLenum)type);
	glShaderSource(shader, 1, &shaderData, NULL);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

		const char* msg = infoLog.data();
		LOG("Could not compile shader: %s. << %s >>", filename, msg);
		valid = false;
	}
	else LOG("Shader compiled: %s", filename);

	delete shaderData;

	return shader;
}

void Shader::SetUniform4x4(const char * name, float * entry)
{
	glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_TRUE, entry);
}

void Shader::SetUniform4(const char * name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(program, name), x, y, z, w);
}

void Shader::SetUniform3(const char * name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(program, name), x, y, z);
}
