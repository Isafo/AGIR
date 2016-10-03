#include <vector>

#include "glm/glm.hpp"

#include "Triangle.h"

const std::vector<Triangle> c_triangles{

	// green wall
	Triangle(
		glm::vec3(0.0f, 5.0f, -6.0f),
		glm::vec3(0.0f, -5.0f, -6.0f),
		glm::vec3(10.0f, -5.0f, -6.0f),
		0.0f,
		1.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f
	),

	Triangle(
		glm::vec3(0.0f, 5.0f, -6.0f),
		glm::vec3(10.0f, -5.0f, -6.0f),
		glm::vec3(10.0f, 5.0f, -6.0f),
		0.0f,
		1.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f
	),

	//blue wall
	Triangle(
		glm::vec3(0.0f, -5.0f, 6.0f),
		glm::vec3(0.0f, 5.0f, 6.0f),
		glm::vec3(10.0f, 5.0f, 6.0f),
		0.0f,
		0.0f,
		1.0f,
		0.0f,
		0.0f,
		0.0f
	),

	Triangle(
		glm::vec3(0.0f, -5.0f, 6.0f),
		glm::vec3(10.0f, 5.0f, 6.0f),
		glm::vec3(10.0f, -5.0f, 6.0f),
		0.0f,
		0.0f,
		1.0f,
		0.0f,
		0.0f,
		0.0f
	),

	// cyan wall
	Triangle(
		glm::vec3(-3.0f, -5.0f, 0.0f),
		glm::vec3(0.0f, -5.0f, -6.0f),
		glm::vec3(0.0f, 5.0f, -6.0f),
		0.0f,
		1.0f,
		1.0f,
		0.0f,
		0.0f,
		0.0f
	),

	Triangle(
		glm::vec3(-3.0f, -5.0f, 0.0f),
		glm::vec3(0.0f, 5.0f, -6.0f),
		glm::vec3(-3.0f, 5.0f, 0.0f),
		0.0f,
		1.0f,
		1.0f,
		0.0f,
		0.0f,
		0.0f
	),

	// magenta wall
	Triangle(
		glm::vec3(0.0f, -5.0f, 6.0f),
		glm::vec3(-3.0f, -5.0f, 0.0f),
		glm::vec3(-3.0f, 5.0f, 0.0f),
		1.0f,
		0.0f,
		1.0f,
		0.0f,
		0.0f,
		0.0f
	),

	Triangle(
		glm::vec3(0.0f, -5.0f, 6.0f),
		glm::vec3(-3.0f, 5.0f, 0.0f),
		glm::vec3(0.0f, 5.0f, 6.0f),
		1.0f,
		0.0f,
		1.0f,
		0.0f,
		0.0f,
		0.0f
	),


	// yellow wall
	Triangle(
		glm::vec3(10.0f, 5.0f, -6.0f),
		glm::vec3(10.0f, -5.0f, -6.0f),
		glm::vec3(13.0f, -5.0f, 0.0f),
		1.0f,
		1.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f
	),

	Triangle(
		glm::vec3(10.0f, 5.0f, -6.0f),
		glm::vec3(13.0f, -5.0f, 0.0f),
		glm::vec3(13.0f, 5.0f, 0.0f),
		1.0f,
		1.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f
	),

	// red wall
	Triangle(
		glm::vec3(10.0f, -5.0f, 6.0f),
		glm::vec3(10.0f, 5.0f, 6.0f),
		glm::vec3(13.0f, 5.0f, 0.0f),
		1.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f
	),

	Triangle(
		glm::vec3(10.0f, -5.0f, 6.0f),
		glm::vec3(13.0f, 5.0f, 0.0f),
		glm::vec3(13.0f, -5.0f, 0.0f),
		1.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f
	),

	// floor
	Triangle(
		glm::vec3(5.0f, -5.0f, 0.0f),
		glm::vec3(0.0f, -5.0f, -6.0f),
		glm::vec3(-3.0f, -5.0f, 0.0f),
		0.8f,
		0.8f,
		0.8f,
		0.0f,
		0.0f,
		0.0f
	),

	Triangle(
		glm::vec3(5.0f, -5.0f, 0.0f),
		glm::vec3(10.0f, -5.0f, -6.0f),
		glm::vec3(0.0f, -5.0f, -6.0f),
		0.8f,
		0.8f,
		0.8f,
		0.0f,
		0.0f,
		0.0f
	),

	Triangle(
		glm::vec3(5.0f, -5.0f, 0.0f),
		glm::vec3(13.0f, -5.0f, 0.0f),
		glm::vec3(10.0f, -5.0f, -6.0f),
		0.8f,
		0.8f,
		0.8f,
		0.0f,
		0.0f,
		0.0f
	),

	Triangle(
		glm::vec3(5.0f, -5.0f, 0.0f),
		glm::vec3(10.0f, -5.0f, 6.0f),
		glm::vec3(13.0f, -5.0f, 0.0f),
		0.8f,
		0.8f,
		0.8f,
		0.0f,
		0.0f,
		0.0f
	),

	Triangle(
		glm::vec3(5.0f, -5.0f, 0.0f),
		glm::vec3(0.0f, -5.0f, 6.0f),
		glm::vec3(10.0f, -5.0f, 6.0f),
		0.8f,
		0.8f,
		0.8f,
		0.0f,
		0.0f,
		0.0f
	),

	Triangle(
		glm::vec3(5.0f, -5.0f, 0.0f),
		glm::vec3(-3.0f, -5.0f, 0.0f),
		glm::vec3(0.0f, -5.0f, 6.0f),
		0.8f,
		0.8f,
		0.8f,
		0.0f,
		0.0f,
		0.0f
	),

	// roof
	Triangle(
		glm::vec3(-3.0f, 5.0f, 0.0f),
		glm::vec3(0.0f, 5.0f, -6.0f),
		glm::vec3(5.0f, 5.0f, 0.0f),
		0.8f,
		0.8f,
		0.8f,
		0.0f,
		0.0f,
		0.0f
	),

	Triangle(
		glm::vec3(0.0f, 5.0f, -6.0f),
		glm::vec3(10.0f, 5.0f, -6.0f),
		glm::vec3(5.0f, 5.0f, 0.0f),
		0.8f,
		0.8f,
		0.8f,
		0.0f,
		0.0f,
		0.0f
	),

	Triangle(
		glm::vec3(10.0f, 5.0f, -6.0f),
		glm::vec3(13.0f, 5.0f, 0.0f),
		glm::vec3(5.0f, 5.0f, 0.0f),
		0.8f,
		0.8f,
		0.8f,
		0.0f,
		0.0f,
		0.0f
	),

	Triangle(
		glm::vec3(13.0f, 5.0f, 0.0f),
		glm::vec3(10.0f, 5.0f, 6.0f),
		glm::vec3(5.0f, 5.0f, 0.0f),
		0.8f,
		0.8f,
		0.8f,
		0.0f,
		0.0f,
		0.0f
	),

	Triangle(
		glm::vec3(10.0f, 5.0f, 6.0f),
		glm::vec3(0.0f, 5.0f, 6.0f),
		glm::vec3(5.0f, 5.0f, 0.0f),
		0.8f,
		0.8f,
		0.8f,
		0.0f,
		0.0f,
		0.0f
	),

	Triangle(
		glm::vec3(0.0f, 5.0f, 6.0f),
		glm::vec3(-3.0f, 5.0f, 0.0f),
		glm::vec3(5.0f, 5.0f, 0.0f),
		0.8f,
		0.8f,
		0.8f,
		0.0f,
		0.0f,
		0.0f
	),

	//Tetrahedron
	Triangle(
		glm::vec3(10.0f, -1.0f, 0.0f),
		glm::vec3(8.0, -4.98f, 0.0f),
		glm::vec3(12.0f, -4.98f, 2.0f),
		1.0f,
		1.0f,
		1.0f,
		0.0f,
		0.0f,
		0.0f
	),

	Triangle(
		glm::vec3(10.0f, -1.0f, 0.0f),
		glm::vec3(12.0f, -4.98f, -2.0f),
		glm::vec3(8.0, -4.98f, 0.0f),
		1.0f,
		1.0f,
		1.0f,
		0.0f,
		0.0f,
		0.0f
	),

	Triangle(
		glm::vec3(10.0f, -1.0f, 0.0f),
		glm::vec3(12.0f, -4.98f, -2.0f),
		glm::vec3(12.0f, -4.98f, 2.0f),
		1.0f,
		1.0f,
		1.0f,
		0.0f,
		0.0f,
		0.0f
	),

	Triangle(
		glm::vec3(8.0, -4.98f, 0.0f),
		glm::vec3(12.0f, -4.98f, 2.0f),
		glm::vec3(12.0f, -4.98f, -2.0f),
		1.0f,
		1.0f,
		1.0f,
		0.0f,
		0.0f,
		0.0f
	),
};