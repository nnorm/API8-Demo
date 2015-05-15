#pragma once

#include <glm/glm.hpp>
using glm::vec3;
using glm::vec4;

class Particle
{
public:
	Particle(vec3 initialPosition, vec4 initalColor, float lifeSpan);
	~Particle();

private: 
	vec3 _position;
	vec3 _velocity;
	vec4 _color;
	float _age;
	float _lifespan;
};

