#pragma once
#include "glm/glm.hpp"

struct Camera 
{
	Camera(glm::vec3 position)
		: m_pos{position}
	{
		m_forward = glm::normalize(-m_pos);
		m_right = glm::cross(m_forward, glm::vec3(0.0f, 1.0f, 0.0f));
		m_up = glm::cross(m_forward, m_right);
	}
	
	glm::vec3 m_pos;
	glm::vec3 m_forward;
	glm::vec3 m_right;
	glm::vec3 m_up;
};