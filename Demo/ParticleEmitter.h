#pragma once

#include <vector>
#include "Particle.h"


class ParticleEmitter
{
public:
	ParticleEmitter();
	std::vector< Particle > emit(int quantity, glm::vec4* initialColor);
	~ParticleEmitter();
private: 
	glm::vec3 _position;
};