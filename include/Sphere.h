#pragma once
#include "glm/glm.hpp"

#include "Ray.h"
#include "Material.h"

struct Sphere 
{
	Sphere(const glm::vec3 p, float r,
		float dR, float dG, float dB, float eR, float eG, float eB, float albedo)
		: m_position(p), m_radius(r)
	{
		m_material.m_diffuse.m_r = dR;
		m_material.m_diffuse.m_g = dG;
		m_material.m_diffuse.m_b = dB;
		m_material.m_emmisive.m_r = eR;
		m_material.m_emmisive.m_g = eG;
		m_material.m_emmisive.m_b = eB;
		m_material.albedo = albedo;
	};

	glm::vec3 m_position;
	float m_radius;
	TriMaterial m_material;
};

inline bool rayIntersection(const Sphere* sphere, const Ray* ray, RayIntersectionData* data)
{
	glm::vec3 s_pos = sphere->m_position;
	float s_radius = sphere->m_radius;
	glm::vec3 r_origin = ray->m_pos;
	glm::vec3 r_dir = ray->m_dir;

	glm::vec3 m = r_origin - s_pos;

	float b = glm::dot(m, r_dir);
	float c = glm::dot(m, m) - s_radius * s_radius;

	// check if ray is pointing away from sphere or
	// if rays's origin is outside of sphere
	if (c > 0.0f && b > 0.0f)
		return false;

	const float d = b * b - c;

	// if the discriminant is negativ then the ray don't intersect the sphere
	if (d <= 0.0f)
		return false;

	float t = -b - sqrt(d);

	if(t < 0.0f)
		t = -b + sqrt(d);

	// compare to earlier collision
	if (data->m_time >= 0.0f && t > data->m_time)
		return false;

	glm::vec3 intersection_point = (r_origin + r_dir * t);
	glm::vec3 normal = glm::normalize(intersection_point - s_pos);

	// Swap the normal direction if we hit the triangle form the inside
	if (glm::dot(normal, r_dir) > 0.0f)
		normal *= glm::vec3(-1.0);

	data->m_time = t;
	data->m_intersectionPoint = intersection_point;
	data->m_normal = normal;
	data->m_material = sphere->m_material;
	
	return true;
}