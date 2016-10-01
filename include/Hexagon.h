#pragma once
#include <memory>

#include "glm/glm.hpp"

#include "Triangle.h"

struct Hexagon
{
	// floor
	Hexagon()
	{
		m_traingles[0] = std::make_unique<Triangle>
		(
			glm::vec3(5.0f, -5.0f, 0.0f),
			glm::vec3(-3.0f, -5.0f, 0.0f),
			glm::vec3(0.0f, -5.0f, -6.0f),
			0.9f, 0.9f, 0.9f, 0.0f, 0.0f, 0.0f
		);

		m_traingles[1] = std::make_unique<Triangle>
		(
			glm::vec3(5.0f, -5.0f, 0.0f),
			glm::vec3(10.0f, -5.0f, -6.0f),
			glm::vec3(0.0f, -5.0f, -6.0f),
			0.9f, 0.9f, 0.9f, 0.0f, 0.0f, 0.0f
		);

		m_traingles[2] = std::make_unique<Triangle>
		(
			glm::vec3(5.0f, -5.0f, 0.0f),
			glm::vec3(13.0f, -5.0f, 0.0f),
			glm::vec3(10.0f, -5.0f, -6.0f),
			0.9f, 0.9f, 0.9f, 0.0f, 0.0f, 0.0f
		);

		m_traingles[3] = std::make_unique<Triangle>
		(
			glm::vec3(5.0f, -5.0f, 0.0f),
			glm::vec3(13.0f, -5.0f, 0.0f),
			glm::vec3(10.0f, -5.0f, 6.0f),
			0.9f, 0.9f, 0.9f, 0.0f, 0.0f, 0.0f
		);

		m_traingles[4] = std::make_unique<Triangle>
		(
			glm::vec3(5.0f, -5.0f, 0.0f),
			glm::vec3(10.0f, -5.0f, 6.0f),
			glm::vec3(0.0f, -5.0f, 6.0f),
			0.9f, 0.9f, 0.9f, 0.0f, 0.0f, 0.0f
		);

		m_traingles[5] = std::make_unique<Triangle>
		(
			glm::vec3(5.0f, -5.0f, 0.0f),
			glm::vec3(0.0f, -5.0f, 6.0f),
			glm::vec3(-3.0f, -5.0f, 0.0f),
			0.9f, 0.9f, 0.9f, 0.0f, 0.0f, 0.0f
		);
	}

	// roof
	Hexagon(bool)
	{
		m_traingles[0] = std::make_unique<Triangle>
		(
			glm::vec3(-3.0f, 5.0f, 0.0f),
			glm::vec3(0.0f, 5.0f, -6.0f),
			glm::vec3(5.0f, 5.0f, 0.0f),
			0.9f, 0.9f, 0.9f, 0.0f, 0.0f, 0.0f
		);

		m_traingles[1] = std::make_unique<Triangle>
		(
			glm::vec3(0.0f, 5.0f, -6.0f),
			glm::vec3(10.0f, 5.0f, -6.0f),
			glm::vec3(5.0f, 5.0f, 0.0f),
			0.9f, 0.9f, 0.9f, 0.0f, 0.0f, 0.0f
		);

		m_traingles[2] = std::make_unique<Triangle>
		(
			glm::vec3(10.0f, 5.0f, -6.0f),
			glm::vec3(13.0f, 5.0f, 0.0f),
			glm::vec3(5.0f, 5.0f, 0.0f),
			0.9f, 0.9f, 0.9f, 0.0f, 0.0f, 0.0f
		);

		m_traingles[3] = std::make_unique<Triangle>
		(
			glm::vec3(13.0f, 5.0f, 0.0f),
			glm::vec3(10.0f, 5.0f, 6.0f),
			glm::vec3(5.0f, 5.0f, 0.0f),
			0.9f, 0.9f, 0.9f, 0.0f, 0.0f, 0.0f
		);

		m_traingles[4] = std::make_unique<Triangle>
		(
			glm::vec3(10.0f, 5.0f, 6.0f),
			glm::vec3(0.0f, 5.0f, 6.0f),
			glm::vec3(5.0f, 5.0f, 0.0f),
			0.9f, 0.9f, 0.9f, 0.0f, 0.0f, 0.0f
		);

		m_traingles[5] = std::make_unique<Triangle>
		(
			glm::vec3(0.0f, 5.0f, 6.0f),
			glm::vec3(-3.0f, 5.0f, 0.0f),
			glm::vec3(5.0f, 5.0f, 0.0f),
			0.9f, 0.9f, 0.9f, 0.0f, 0.0f, 0.0f
		);
	}

	std::unique_ptr<Triangle> m_traingles[6];
};