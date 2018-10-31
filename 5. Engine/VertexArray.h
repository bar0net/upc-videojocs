#pragma once

#define VA_Float 0x1406
#define VA_UNSIGNED_INT 0x1405
#define VA_UNSIGNED_BYTE 0x1401

class VertexBuffer;

class VertexArray
{
public:
	VertexArray();
	virtual ~VertexArray();

	void Bind() const;
	void UnBind() const;

	void AddAttrib(VertexBuffer* vbo, unsigned int count, unsigned int type, unsigned int stride, unsigned int offset);

	unsigned int vao;
	unsigned int id = 0;
};