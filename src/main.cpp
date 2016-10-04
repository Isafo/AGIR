#include "glm/glm.hpp"

#include "Sphere.h"
#include "Camera.h"
#include "Ray.h"
#include "Triangle.h"
#include "Image.h"
#include "triangleScene.h"

#include <iostream>
#include <array>
#include <random>
#include "math.h"

#define D_EPSILON 0.001
#define D_PI 3.1415926536

const unsigned int C_MAX_BOUNCES = 5;

const std::array<Sphere, 1> c_spheres{
	{Sphere(glm::vec3(8.0f, 0.0f, -1.0f), 1.0f, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0) }
};

const glm::vec3 pointLightPos = glm::vec3(5.0f, 3.0f, 0.0f);

inline void renderPixels(Image* img, Camera* cam);
inline PixelRGB L_in(Ray* ray);
inline glm::vec3 L_out(RayIntersectionData* inData, Ray* ray, int nrBounces);
inline bool findClosestIntersection(Ray* ray, RayIntersectionData* intersectionData);
inline bool perfectReflectedRay(Ray* ray, RayIntersectionData* intersectionData);
inline bool shadowRay(RayIntersectionData* intersectionData);
float getRandomFloat();
inline glm::vec3 uniformSampleHemisphere(const glm::vec3 &n);

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
/*
	perfectReflectedRay(ray, &iD);

	shadowRay(&iD);
*/
	glm::vec3 result = L_out(&iD, ray, 0);

	PixelRGB pixelColor;
	pixelColor.m_r = result.r;
	pixelColor.m_g = result.g;
	pixelColor.m_b = result.b;

	return pixelColor;
	//return iD.m_material.m_diffuse;
}

inline glm::vec3 L_out(RayIntersectionData* inData, Ray* ray, int nrBounces)
{
	glm::vec3 rayMissColor = glm::vec3(0.0f);

	if (nrBounces == C_MAX_BOUNCES)
		return rayMissColor;

	glm::vec3 inEmmissive = glm::vec3(inData->m_material.m_emmisive.m_r, inData->m_material.m_emmisive.m_g, inData->m_material.m_emmisive.m_b);
	glm::vec3 inDiffuse = glm::vec3(inData->m_material.m_diffuse.m_r, inData->m_material.m_diffuse.m_g, inData->m_material.m_diffuse.m_b);
	glm::vec3 surfaceNormal = inData->m_normal;

	glm::vec3 result = inEmmissive;

	// randomize ray direction
	Ray newRay;
	newRay.m_dir = uniformSampleHemisphere(surfaceNormal);

	// move the new ray position a small amount away from the intersection to 
	// avoid self intersection
	newRay.m_pos = inData->m_intersectionPoint + glm::vec3(D_EPSILON) * newRay.m_dir;

	// calculate the rendering eq
	RayIntersectionData data;
	// multiplication by 2 is because of the PDF
	if (findClosestIntersection(&newRay, &data)) 
		result += 2.0f * L_out(&data, &newRay, nrBounces + 1) * inDiffuse * glm::dot(newRay.m_dir, surfaceNormal);
	else 
		result += 2.0f * rayMissColor * inDiffuse * glm::dot(newRay.m_dir, surfaceNormal);
	
	return result;
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

float getRandomFloat()
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