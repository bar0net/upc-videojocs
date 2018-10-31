#include "VertexBuffer.h"

#include "GL/glew.h"

VertexBuffer::VertexBuffer(unsigned int elements, float* vertices)
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	while (glGetError() != GL_NO_ERROR);
	glBufferData(GL_ARRAY_BUFFER, elements * sizeof(float), vertices, GL_STATIC_DRAW);
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) __debugbreak();
}

VertexBuffer::~VertexBuffer()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	if (vbo != 0) glDeleteBuffers(1, &vbo);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
