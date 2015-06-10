#pragma once
#include "Common.h"

enum bufferType
{
	VAO,
	VBO = GL_VERTEX_ARRAY,
	FBO = GL_FRAMEBUFFER,
	EBO = GL_ELEMENT_ARRAY_BUFFER,
	TFB = GL_TRANSFORM_FEEDBACK_BUFFER
};

class Buffer
{
public:
	Buffer(bufferType type);
	~Buffer();

	bufferType getType();
	unsigned int getID();
	void bind();
	void unbind();

private:
	unsigned int _id;
	bufferType _type;
};