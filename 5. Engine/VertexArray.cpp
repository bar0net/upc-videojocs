#include "VertexArray.h"

#include "GL/glew.h"
#include "VertexBuffer.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &vao);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &vao);
}

void VertexArray::Bind() const
{
	glBindVertexArray(vao);
}

void VertexArray::UnBind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddAttrib(VertexBuffer * vbo, unsigned int count, unsigned int type, unsigned int stride, unsigned int offset)
{
	Bind();
	vbo->Bind();
	while (glGetError() != GL_NO_ERROR);
	glEnableVertexAttribArray(id);
	glVertexAttribPointer(id, count, type, GL_FALSE, stride, (const void*)offset);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) __debugbreak();
	++id;
}
