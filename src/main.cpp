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

const unsigned int C_MAX_BOUNCES = 5;

const std::array<Sphere, 1> c_spheres{
	{Sphere(glm::vec3(8.0f, 0.0f, -1.0f), 1.0f, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0) }
};

const glm::vec3 pointLightPos = glm::vec3(5.0f, 3.0f, 0.0f);

inline void renderPixels(Image* img, Camera* cam);
inline PixelRGB L_in(Ray* ray);
inline PixelRGB L_out(Ray* ray);
inline bool findClosestIntersection(Ray* ray, RayIntersectionData* intersectionData);
inline bool perfectReflectedRay(Ray* ray, RayIntersectionData* intersectionData);
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

		PixelRGB pixelColor = L_in(&ray);

		img->imgData.r[i] = pixelColor.m_r;
		img->imgData.g[i] = pixelColor.m_g;
		img->imgData.b[i] = pixelColor.m_b;
	}
}

inline PixelRGB L_in(Ray* ray)
{
	RayIntersectionData iD;
	iD.m_material.m_diffuse.m_r = 0.0f;
	iD.m_material.m_diffuse.m_g = 0.0f;
	iD.m_material.m_diffuse.m_b = 0.0f;

	findClosestIntersection(ray, &iD);

	perfectReflectedRay(ray, &iD);

	shadowRay(&iD);

	return iD.m_material.m_diffuse;
}

inline PixelRGB L_out(RayIntersectionData* inData, Ray* ray, int nrBounces)
{
	PixelRGB rayMissColor;
	rayMissColor.m_r = 1.0f;
	rayMissColor.m_g = 0.2f;
	rayMissColor.m_b = 0.0f;

	if (nrBounces == C_MAX_BOUNCES)
		return rayMissColor;

	PixelRGB inEmmissive = inData->m_material.m_emmisive;
	PixelRGB inDiffuse = inData->m_material.m_diffuse;

	PixelRGB result = inEmmissive;

	// randomize ray direction
	Ray newRay;
	
	//TODO write a random ray dir generator for the hemisphere
	glm::vec3 randRayDir;

	// TODO: possibly move the start ray out a bit from the surface to avoid the 
	// self intersection problem
	newRay.m_pos = inData->m_intersectionPoint;
	newRay.m_dir = glm::normalize(randRayDir);


	// calculate the rendering eq
	RayIntersectionData data;
	if (findClosestIntersection(&newRay, &data)) {
		
		// TODO: the rendering eq

		result.m_r += 0.0f; 
		result.m_g += 0.0f;
		result.m_b += 0.0f;
	}
	else {

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

inline bool perfectReflectedRay(Ray* ray, RayIntersectionData* intersectionData)
{

	Ray reflectedRay;
	reflectedRay.m_pos = intersectionData->m_intersectionPoint;

	glm::vec3 N = intersectionData->m_normal;
	glm::vec3 I = ray->m_pos + ray->m_dir;

	reflectedRay.m_dir = I - 2.0f * glm::dot(I, N) * N;

	RayIntersectionData reflectedRayIntersection;
	reflectedRayIntersection.m_material.m_diffuse.m_r = 0.0f;
	reflectedRayIntersection.m_material.m_diffuse.m_g = 0.0f;
	reflectedRayIntersection.m_material.m_diffuse.m_b = 0.0f;

	findClosestIntersection(&reflectedRay, &reflectedRayIntersection);

	intersectionData->m_material.m_diffuse.m_r = intersectionData->m_material.m_diffuse.m_r * 0.8f + reflectedRayIntersection.m_material.m_diffuse.m_r * 0.2f;
	intersectionData->m_material.m_diffuse.m_g = intersectionData->m_material.m_diffuse.m_g * 0.8f + reflectedRayIntersection.m_material.m_diffuse.m_g * 0.2f;
	intersectionData->m_material.m_diffuse.m_b = intersectionData->m_material.m_diffuse.m_b * 0.8f + reflectedRayIntersection.m_material.m_diffuse.m_b * 0.2f;

	return true;
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