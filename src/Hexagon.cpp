#include "Hexagon.h"

// roof
Hexagon::Hexagon(bool)
{
	m_t1 = std::make_unique<Triangle>
		(
			glm::vec3(-3.0f, 5.0f, 0.0f),
			glm::vec3(0.0f, 5.0f, -6.0f),
			glm::vec3(5.0f, 5.0f, 0.0f)
		);

	m_t2 = std::make_unique<Triangle>
		(
			glm::vec3(0.0f, 5.0f, -6.0f),
			glm::vec3(10.0f, 5.0f, -6.0f),
			glm::vec3(5.0f, 5.0f, 0.0f)
		);

	m_t3 = std::make_unique<Triangle>
		(
			glm::vec3(10.0f, 5.0f, -6.0f),
			glm::vec3(13.0f, 5.0f, 0.0f),
			glm::vec3(5.0f, 5.0f, 0.0f)
		);

	m_t4 = std::make_unique<Triangle>
		(
			glm::vec3(13.0f, 5.0f, 0.0f),
			glm::vec3(10.0f, 5.0f, 6.0f),
			glm::vec3(5.0f, 5.0f, 0.0f)
		);

	m_t5 = std::make_unique<Triangle>
		(
			glm::vec3(10.0f, 5.0f, 6.0f),
			glm::vec3(0.0f, 5.0f, 6.0f),
			glm::vec3(5.0f, 5.0f, 0.0f)
		);

	m_t6 = std::make_unique<Triangle>
		(
			glm::vec3(0.0f, 5.0f, 6.0f),
			glm::vec3(-3.0f, 5.0f, 0.0f),
			glm::vec3(5.0f, 5.0f, 0.0f)
		);
}

// floor
Hexagon::Hexagon()
{
	m_t1 = std::make_unique<Triangle>
		(
			glm::vec3(5.0f, -5.0f, 0.0f),
			glm::vec3(-3.0f, -5.0f, 0.0f),
			glm::vec3(0.0f, -5.0f, -6.0f)
		);

	m_t2 = std::make_unique<Triangle>
		(
			glm::vec3(5.0f, -5.0f, 0.0f),
			glm::vec3(10.0f, -5.0f, -6.0f),
			glm::vec3(0.0f, -5.0f, -6.0f)
		);

	m_t3 = std::make_unique<Triangle>
		(
			glm::vec3(5.0f, -5.0f, 0.0f),
			glm::vec3(13.0f, -5.0f, 0.0f),
			glm::vec3(10.0f, -5.0f, -6.0f)
		);

	m_t4 = std::make_unique<Triangle>
		(
			glm::vec3(5.0f, -5.0f, 0.0f),
			glm::vec3(13.0f, -5.0f, 0.0f),
			glm::vec3(10.0f, -5.0f, 6.0f)

		);

	m_t5 = std::make_unique<Triangle>
		(

			glm::vec3(5.0f, -5.0f, 0.0f),
			glm::vec3(10.0f, -5.0f, 6.0f),
			glm::vec3(0.0f, -5.0f, 6.0f)
		);

	m_t6 = std::make_unique<Triangle>
		(
			glm::vec3(5.0f, -5.0f, 0.0f),
			glm::vec3(0.0f, -5.0f, 6.0f),
			glm::vec3(-3.0f, -5.0f, 0.0f)
		);
}