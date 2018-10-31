#pragma once

class VertexBuffer
{
public:
	VertexBuffer(unsigned int elements, float* vertices);
	virtual ~VertexBuffer();

	void Bind() const;
	void UnBind() const;

	unsigned int vbo;
};
