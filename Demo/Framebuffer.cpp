#include "Framebuffer.h"


Framebuffer::Framebuffer()
{
	glGenFramebuffers(1, &this->_id);
}

Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &this->_id);
}

void Framebuffer::Bind(int target)
{
	glBindFramebuffer(this->_targets[target], this->_id);
}

void Framebuffer::Unbind(int target)
{
	glBindFramebuffer(this->_targets[target], 0);
}

void Framebuffer::AttachTarget(unsigned int target)
{
	this->_targets.push_back(target);
}

void Framebuffer::AttachDepthTarget(unsigned int target)
{
	this->_depthTarget = target;
}

unsigned int Framebuffer::GetTarget(int i)
{
	return this->_targets[i];
}

unsigned int Framebuffer::GetDepthTarget()
{
	return this->_depthTarget;
}