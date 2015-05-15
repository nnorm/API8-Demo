#pragma once

#include <vector>
#include "Particle.h"
#include "ParticleEmitter.h"

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

private:
	vec3 _size;
	int _maxParticles;
	std::vector < ParticleEmitter > _emitters;
	std::vector < Particle > _particles;
};

