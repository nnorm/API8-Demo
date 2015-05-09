#include "Framebuffer.h"


Framebuffer::Framebuffer()
{
	glGenFramebuffers(1, &this->_id);
}

Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &this->_id);
}

void Framebuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, this->_id);
}

void Framebuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::AttachTarget(GLuint target)
{
	Bind();
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + this->_targets.size(), target, 0);
	Unbind();
	this->_targets.push_back(target);
}

void Framebuffer::AttachDepthTarget(GLuint target)
{
	Bind();
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, target, 0);
	Unbind();
	this->_depthTarget = target;
}

GLuint Framebuffer::GetTarget(int i)
{
	return this->_targets[i];
}

GLuint Framebuffer::GetDepthTarget()
{
	return this->_depthTarget;
}