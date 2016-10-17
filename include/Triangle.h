#pragma once

#define EPSILON 0.00001

#include "glm/glm.hpp"

#include "Ray.h"
#include "Material.h"

struct Triangle 
{
	Triangle(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, 
		float dR, float dG, float dB, float eR, float eG, float eB, float albedo)
		: m_a(a), m_b(b), m_c(c)
	{
		m_normal = glm::normalize(glm::cross(m_b - m_a, m_c - m_a));
		m_material.m_diffuse.m_r = dR;
		m_material.m_diffuse.m_g = dG;
		m_material.m_diffuse.m_b = dB;
		m_material.m_emmisive.m_r = eR;
		m_material.m_emmisive.m_g = eG;
		m_material.m_emmisive.m_b = eB;
		m_material.albedo = albedo;
	}

	glm::vec3 m_a;
	glm::vec3 m_b;
	glm::vec3 m_c;
	TriMaterial m_material;
	glm::vec3 m_normal;
};

inline bool rayIntersection(const Triangle* tri, const Ray* ray, RayIntersectionData* data)
{
	const glm::vec3 d = ray->m_dir;
	const glm::vec3 o = ray->m_pos;

	const glm::vec3 v0 = tri->m_a;
	const glm::vec3 v1 = tri->m_b;
	const glm::vec3 v2 = tri->m_c;
	glm::vec3 normal = tri->m_normal;

	glm::vec3 e1 = v1 - v0;
	glm::vec3 e2 = v2 - v0;

	glm::vec3 p = glm::cross(d, e2);
	
	const float det = glm::dot(e1, p);

	if (abs(det) < EPSILON)
		return false;

	const glm::vec3 T = (o - v0) / det;
	const glm::vec3 q = glm::cross(T, e1);

	// barycentric coordiantes
	const float u = glm::dot(T, p);
	const float v = glm::dot(d, q);
	const float w = 1.0f - u - v;

	 // check if the intersection point is inside the triangle
	if (u < 0.0f || v < 0.0f || w < 0.0f)
		return false;

	float t = glm::dot(e2, q);

	if (t < EPSILON)
		return false;

	// compare to earlier collision
	if (data->m_time >= 0.0f && t > data->m_time)
		return false;

	// Swap the normal direction if we hit the triangle form the inside
	if (glm::dot(normal, d) > 0.0f)
		normal *= glm::vec3(-1.0);

	data->m_time = t;
	data->m_intersectionPoint = o + d * t;
	data->m_normal = normal;
	data->m_material = tri->m_material;

	return true;
}