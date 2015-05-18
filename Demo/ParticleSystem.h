#pragma once

#include <vector>
#include "Particle.h"
#include "ParticleEmitter.h"

class ParticleSystem
{
public:
	ParticleSystem(unsigned int _geometryShader);

	void update();
	void render();

	~ParticleSystem();

private:
	glm::vec3 _size;
	int _maxParticles;
	unsigned int _geometryShader;
	std::vector < ParticleEmitter > _emitters;
	std::vector < Particle > _particles;
};

