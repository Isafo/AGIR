#include <array>
#include <vector>

#include <glm/glm.hpp>

#include "Image.h"
#include "Plane.h"
#include "Sphere.h"
#include "Hexagon.h"
#include "Tetrahedron.h"
#include "Ray.h"
#include "Camera.h"
#include "triangleScene.h"


#define D_RESOLUTION 1000000

inline void renderPixels(Image* img, Camera* cam);
inline bool findClosestIntersection(Ray* ray, RayIntersectionData* intersectionData);

const std::array<Plane, 6> C_PLANES = {
	Plane(glm::vec3(0.0f, -5.0f, -6.0f), glm::vec3(0.0f, 5.0f, -6.0f), glm::vec3(10.0f, 5.0f, -6.0f), glm::vec3(10.0f, -5.0f, -6.0f),
		  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f),
	Plane(glm::vec3(0.0f, -5.0f, 6.0f), glm::vec3(0.0f, 5.0f, 6.0f), glm::vec3(10.0f, 5.0f, 6.0f), glm::vec3(10.0f, -5.0f, 6.0f),
		  0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f),
	Plane(glm::vec3(0.0f, -5.0f, -6.0f), glm::vec3(-3.0f, -5.0f,  0.0f), glm::vec3(-3.0f,  5.0f,  0.0f), glm::vec3(0.0f,  5.0f, -6.0f),
		  0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f),
	Plane(glm::vec3(0.0f, -5.0f, 6.0f), glm::vec3(-3.0f, -5.0f, 0.0f), glm::vec3(-3.0f, 5.0f, 0.0f),  glm::vec3(0.0f, 5.0f, 6.0f),
		  0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f),
	Plane(glm::vec3(10.0f, 5.0f, -6.0f), glm::vec3(10.0f, -5.0f, -6.0f), glm::vec3(13.0f, -5.0f, 0.0f), glm::vec3(13.0f, 5.0f, 0.0f),
		  0.0f, 0.8f, 1.0f, 0.0f, 0.0f, 0.0f),
	Plane(glm::vec3(10.0f, -5.0f, 6.0f), glm::vec3(10.0f, 5.0f, 6.0f), glm::vec3(13.0f, 5.0f, 0.0f),	glm::vec3(13.0f, -5.0f, 0.0f),
		  1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f),
};

const std::array<Hexagon, 2> C_HEX = {
	Hexagon(),
	Hexagon(true)
};


int main()
{
	Image img;

	Camera cam(glm::vec3(-1.0f, 0.0, 0.0));

	renderPixels(&img, &cam);
	img.saveBMP();
}

inline void renderPixels(Image* img, Camera* cam)
{
	Ray ray;
	ray.m_pos.x = 0.0f;
	
	float y, z, u, v;
	int pixelIndex;
	int img_width = img->x;

	for (int i = 0; i < D_RESOLUTION; ++i)
	{
		// caluclate the pixel world coordinates and index in img data
		u = (i % img_width);
		v = (i / img_width);
		z = (u / 1000.0f) * 2.0f - 1.0f;
		y = (v / 1000.0f) * 2.0f - 1.0f;
		pixelIndex = v * img_width + u;

		ray.m_pos.y = y;
		ray.m_pos.z = z;

		ray.m_dir = glm::normalize(ray.m_pos - cam->m_pos);
		
		RayIntersectionData intersectionData;
		findClosestIntersection(&ray, &intersectionData);
		img->imgData.r[pixelIndex] = intersectionData.m_material.m_diffuse.m_r;
		img->imgData.g[pixelIndex] = intersectionData.m_material.m_diffuse.m_g;
		img->imgData.b[pixelIndex] = intersectionData.m_material.m_diffuse.m_b;
	}
}

inline bool findClosestIntersection(Ray* ray, RayIntersectionData* intersectionData)
{
	bool intersected = false;
	// TODO: redesign this in such a way that all triangles for an entity can be sent at once
	//for (const auto& p : C_PLANES)
	//{
	//	intersected |= rayIntersection(p.m_triangles[0].get(), ray, intersectionData);
	//	intersected |= rayIntersection(p.m_triangles[0].get(), ray, intersectionData);
	//}
	// TODO: redesign this in such a way that all triangles for an entity can be sent at once
	//for (const auto& h : C_HEX)
	//{
	//	intersected |= rayIntersection(h.m_traingles[0].get(), ray, intersectionData);
	//	intersected |= rayIntersection(h.m_traingles[1].get(), ray, intersectionData);
	//	intersected |= rayIntersection(h.m_traingles[2].get(), ray, intersectionData);
	//	intersected |= rayIntersection(h.m_traingles[3].get(), ray, intersectionData);
	//	intersected |= rayIntersection(h.m_traingles[4].get(), ray, intersectionData);
	//	intersected |= rayIntersection(h.m_traingles[5].get(), ray, intersectionData);
	//}

	for (const auto& t : triangles) {
		intersected |= rayIntersection(&t, ray, intersectionData);
	}

	return intersected;
}