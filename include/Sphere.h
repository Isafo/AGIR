#pragma once
#include "glm/glm.hpp"

// TODO: add material later
class Sphere 
{
public:  
	Sphere(const glm::vec3 p, float r);
	~Sphere() = default;

private:
	glm::vec3 m_position;
	float m_radius;
	//Material m_material;
};