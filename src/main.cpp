#include <glm/glm.hpp>

#include "Image.h"
#include "Plane.h"
#include "Sphere.h"
#include "Hexagon.h"
#include "Tetrahedron.h"

#define M_PI 3.14159265358979323846
#define EPSILON 0.000001

inline void createRoom(std::unique_ptr<Plane>* p, std::unique_ptr<Hexagon>* h);

int main()
{
	Image img;
	img.saveBMP();

	std::unique_ptr<Plane> planes[6];
	std::unique_ptr<Hexagon> hex[6];

	createRoom(planes, hex);

}

inline void createRoom(std::unique_ptr<Plane>* p, std::unique_ptr<Hexagon>* h)
{
	// create the walls of the room
	p[0] = std::make_unique<Plane>
	(
		glm::vec3(0.0f, -5.0f, -6.0f),
		glm::vec3(0.0f, 5.0f, -6.0f),
		glm::vec3(10.0f, 5.0f, -6.0f),
		glm::vec3(10.0f, -5.0f, -6.0f)
	);

	p[1] = std::make_unique<Plane>
	(
		glm::vec3(0.0f, -5.0f, 6.0f),
		glm::vec3(0.0f, 5.0f, 6.0f),
		glm::vec3(10.0f, 5.0f, 6.0f),
		glm::vec3(10.0f, -5.0f, 6.0f)
	);

	p[2] = std::make_unique<Plane>
	(
		glm::vec3( 0.0f, -5.0f, -6.0f),
		glm::vec3(-3.0f, -5.0f,  0.0f),
		glm::vec3(-3.0f,  5.0f,  0.0f),
		glm::vec3( 0.0f,  5.0f, -6.0f)
	);

	p[3] = std::make_unique<Plane>
	(
		glm::vec3(-3.0f, -5.0f, 0.0f),
		glm::vec3(0.0f, -5.0f, 6.0f),
		glm::vec3(0.0f, 5.0f, 6.0f), 
		glm::vec3(-3.0f, 5.0f, 0.0f)
	);

	p[4] = std::make_unique<Plane>
	(
		glm::vec3(10.0f, -5.0f, -6.0f),
		glm::vec3(10.0f, 5.0f, -6.0f),
		glm::vec3(13.0f, 5.0f, 0.0f),
		glm::vec3(13.0f, -5.0f, 0.0f)
	);

	p[5] = std::make_unique<Plane>
	(
		glm::vec3(13.0f, -5.0f, 0.0f),
		glm::vec3(13.0f, 5.0f, 0.0f),
		glm::vec3(10.0f, 5.0f, -6.0f),
		glm::vec3(10.0f, -5.0f, -6.0f)
	);

	// create floor and roof
	h[0] = std::make_unique<Hexagon>();
	h[1] = std::make_unique<Hexagon>(true);
}
