#include "Buffer.h"

Buffer::Buffer(bufferType type)
{
	switch (type)
	{
	case VAO:
		glGenVertexArrays(1, &this->_id);
		break;
	case VBO:
		glGenBuffers(1, &this->_id);
		break;
	case EBO:
		glGenBuffers(1, &this->_id);
		break;
	case FBO:
		glGenFramebuffers(1, &this->_id);
		break;
	default:
		glGenBuffers(1, &this->_id);
		break;
	}
	this->_type = type;
}

Buffer::~Buffer()
{
}

bufferType Buffer::getType()
{
	return this->_type;
}

unsigned int Buffer::getID()
{
	return this->_id;
}

void Buffer::bind()
{
	switch (this->_type)
	{
	case VAO:
		glBindVertexArray(this->_id);
		break;
	case VBO:
		glBindBuffer(GL_ARRAY_BUFFER, this->_id);
		break;
	case FBO:
		glBindBuffer(GL_FRAMEBUFFER, this->_id);
		break;
	case EBO:
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_id);
		break;
	default:
		glBindBuffer(GL_ARRAY_BUFFER, this->_id);
		break;
	}
}

void Buffer::unbind()
{
	switch (this->_type)
	{
	case VAO:
		glBindVertexArray(0);
		break;
	case VBO:
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		break;
	case FBO:
		glBindBuffer(GL_FRAMEBUFFER, 0);
		break;
	case EBO:
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		break;
	default:
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		break;
	}
}