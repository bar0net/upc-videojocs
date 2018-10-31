#pragma once

class IndexBuffer
{
public:
	IndexBuffer(unsigned int elements, unsigned int* indices);
	virtual ~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	unsigned int ibo;
};