#include "Particle.h"


Particle::Particle(glm::vec3* initialPosition, glm::vec4* initalColor, float lifeSpan)
{
	this->_lifespan = lifeSpan;
	this->_color = *initalColor;
	this->_position = glm::vec4(initialPosition->x, initialPosition->y, initialPosition->z, this->_age);
}

glm::vec3 Particle::getPosition()
{
	glm::vec3 p = glm::vec3(this->_position.x, this->_position.y, this->_position.z);
	return p;
}

glm::vec4 Particle::getColor()
{
	return this->_color;
}

Particle::~Particle()
{
}
