#pragma once

#include <vector>
#include "Particle.h"


class ParticleEmitter
{
public:
	ParticleEmitter();
	std::vector< Particle > emit(int quantity);
	~ParticleEmitter();
private: 
	glm::vec3 _position;
	glm::vec3 _velocity;
	float _radius;
};