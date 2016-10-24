#pragma once

#define D_PI 3.1415926536

#include <random>

#include "glm/glm.hpp"

inline float getRandomFloat()
{
	static std::random_device rd;
	static std::mt19937 re(rd());
	static std::uniform_real_distribution<float> dist(0.0f, 1.0f);

	return dist(re);
}

inline glm::vec3 uniformSampleHemisphere(const glm::vec3 &n)
{
	// generate random numbers
	float u = getRandomFloat();
	float v = getRandomFloat();

	float theta = 2 * D_PI * u;
	float phi = acos(2.0f * v - 1.0f);

	// calculate the point on the sphere
	float cosTheta = cos(theta);
	float sinTheta = sin(theta);
	float cosPhi = cos(phi);
	float sinPhi = sin(phi);
	glm::vec3 rayDir = glm::vec3(cosTheta * sinPhi, sinTheta * sinPhi, cosPhi);

	// swap the ray dir if it doesn't point in the surface normal direction
	// to make sure they are within the hemisphere
	float dot = glm::dot(n, rayDir);
	if (dot <= 0.0)
		rayDir = -rayDir;

	return rayDir;
}