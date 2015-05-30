#include "Particle.h"


Particle::Particle(glm::vec3* initialPosition, glm::vec4* initalColor, float lifeSpan)
{
	this->_lifespan = lifeSpan;
	this->_color = *initalColor;
	this->_position = glm::vec4(initialPosition->x, initialPosition->y, initialPosition->z, 0.0f);
}

glm::vec4 Particle::getPositionAge()
{
	return this->_position;
}

glm::vec4 Particle::getColor()
{
	return this->_color;
}

Particle::~Particle()
{
}
