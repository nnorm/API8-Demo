#pragma once
#include "Particle.h"
class ParticleEmitter
{
public:
	ParticleEmitter();
	~ParticleEmitter();
private: 
	glm::vec3 _position;
	glm::vec3 _velocity;
	float _radius;
};

