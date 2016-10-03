#include "glm/glm.hpp"

#include "Sphere.h"
#include "Camera.h"
#include "Ray.h"
#include "Triangle.h"
#include "Image.h"
#include "triangleScene.h"

#include <iostream>
#include <array>

#define D_EPSILON 0.001

const std::array<Sphere, 1> c_spheres{
	{Sphere(glm::vec3(8.0f, 0.0f, -1.0f), 1.0f, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0) }
};

const glm::vec3 pointLightPos = glm::vec3(5.0f, 3.0f, 0.0f);

inline void renderPixels(Image* img, Camera* cam);
inline bool findClosestIntersection(Ray* ray, RayIntersectionData* intersectionData);
inline bool shadowRay(RayIntersectionData* intersectionData);

int main(){

	Image img;

	Camera cam(glm::vec3(-1.0f, 0.0f, 0.0f));

	renderPixels(&img, &cam);

	img.saveBMP();

	std::cout << "\a";
	
	return 0;
}


inline void renderPixels(Image* img, Camera* cam)
{
	Ray ray;
	ray.m_pos.x = 0.0f;

	float y, z, u, v;
	int pixelIndex;
	int img_width = 1000;
	float dz = 1.0f / 1000.0f;
	float dy = 1.0f / 1000.0f;

	for (int i = 0; i < 1000000; ++i)
	{
		// caluclate the pixel world coordinates and index in img data
		u = (i % img_width);
		v = (i / img_width);
		z = ((u / 1000.0f) * 2.0f - 1.0f) + dz;
		y = ((v / 1000.0f) * 2.0f - 1.0f) + dy;
		pixelIndex = v * img_width + u;

		ray.m_pos.y = y;
		ray.m_pos.z = z;

		ray.m_dir = glm::normalize(ray.m_pos - cam->m_pos);

		RayIntersectionData iD;
		iD.m_material.m_diffuse.m_r = 0.0f;
		iD.m_material.m_diffuse.m_g = 0.0f;
		iD.m_material.m_diffuse.m_b = 0.0f;

		findClosestIntersection(&ray, &iD);

		shadowRay(&iD);

		img->imgData.r[i] = iD.m_material.m_diffuse.m_r;
		img->imgData.g[i] = iD.m_material.m_diffuse.m_g;
		img->imgData.b[i] = iD.m_material.m_diffuse.m_b;
	}
}

inline bool findClosestIntersection(Ray* ray, RayIntersectionData* intersectionData)
{
	bool intersected = false;
	for (const auto& t : c_triangles)
		intersected |= rayIntersection(&t, ray, intersectionData);

	for (const auto& s : c_spheres)
		intersected |= rayIntersection(&s, ray, intersectionData);


	return intersected;
}

inline bool shadowRay(RayIntersectionData* intersectionData)
{
	glm::vec3 intersection = intersectionData->m_intersectionPoint;
	glm::vec3 surfaceNormal = intersectionData->m_normal;

	glm::vec3 l_i = intersection - pointLightPos;

	// if the surface normal and vector between the point light and intersection point
	// point in the same direction the area is not lit
	float dot = glm::dot(l_i, surfaceNormal);
	if (dot > 0)
	{
		intersectionData->m_material.m_diffuse.m_r = 0.0f;
		intersectionData->m_material.m_diffuse.m_g = 0.0f;
		intersectionData->m_material.m_diffuse.m_b = 0.0f;
		return false;
	}
		
	Ray ray;
	ray.m_pos = intersection;
	ray.m_dir = glm::normalize(-l_i);

	RayIntersectionData shadowRayIntersection;
	shadowRayIntersection.m_time = -10000.0f;
	shadowRayIntersection.m_intersectionPoint = glm::vec3(1000.0f, 1000.0f, 1000.0f);
	findClosestIntersection(&ray, &shadowRayIntersection);

	float shadowRayLength = glm::length(shadowRayIntersection.m_intersectionPoint - intersection);
	float l_iLength = glm::length(l_i);
	
	if (shadowRayLength < l_iLength  && shadowRayLength > D_EPSILON)
	{
		intersectionData->m_material.m_diffuse.m_r = 0.0f;
		intersectionData->m_material.m_diffuse.m_g = 0.0f;
		intersectionData->m_material.m_diffuse.m_b = 0.0f;
		return false;
	}
	return true;
}