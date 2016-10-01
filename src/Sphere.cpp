#include "Sphere.h"

Sphere::Sphere(const glm::vec3 p, float r, 
	float dR, float dG, float dB, float eR, float eG, float eB)
	: m_position(p), m_radius(r)
{
	m_material.m_diffuse.m_r = dR;
	m_material.m_diffuse.m_g = dG;
	m_material.m_diffuse.m_b = dB;
	m_material.m_emmisive.m_r = eR;
	m_material.m_emmisive.m_g = eG;
	m_material.m_emmisive.m_b = eB;
}

