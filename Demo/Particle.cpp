#include "Particle.h"


Particle::Particle(glm::vec3* initialPosition, glm::vec4* initalColor, float lifeSpan)
{
	this->_lifespan = lifeSpan;
	this->_color = *initalColor;
	this->_position = *initialPosition;
	this->_velocity = glm::vec3(0.0f);
}

glm::vec3 Particle::getPosition()
{
	return this->_position;
}

glm::vec4 Particle::getColor()
{
	return this->_color;
}

glm::vec3 Particle::getVelocity()
{
	return this->_velocity;
}


Particle::~Particle()
{
}
