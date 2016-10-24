#include <iostream>
#include <thread>
#include <atomic>
#include <array>

#include "glm/glm.hpp"

#include "Sphere.h"
#include "Camera.h"
#include "Ray.h"
#include "Triangle.h"
#include "Image.h"
#include "triangleScene.h"
#include "Utils.h"

#define D_EPSILON 0.001f
#define D_RAY_LAUNCH_PROBABILITY 0.1f
#define D_RAYS_PER_PIXEL 10

const int C_MAX_SHADOWRAYS = 1;

std::atomic<size_t> currentPixelIndex(-1);

const std::array<Sphere, 2> c_spheres{
	{ Sphere(glm::vec3(8.0f, -3.5f, -4.0f), 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.75f),
	Sphere(glm::vec3(10.0f, -2.5f, 2.0f), 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.75f) }
};

void renderPixels(Image* img, Camera* cam);
PixelRGB L_in(Ray* ray);
glm::vec3 L_out(RayIntersectionData* inData, Ray* ray);
bool findClosestIntersection(Ray* ray, RayIntersectionData* intersectionData);
bool perfectReflectedRay(Ray* ray, RayIntersectionData* intersectionData);
glm::vec3 shadowRay(RayIntersectionData* intersectionData);

int main(){

	Image img;

	Camera cam(glm::vec3(-1.0f, 0.0f, 0.0f));

	const size_t nrThreads = std::thread::hardware_concurrency();
	printf("Using %i threads.\n", nrThreads);

	if (nrThreads > 1)
	{
		std::vector<std::thread> threads;
		threads.resize(nrThreads);

		for (auto& t : threads)
			t = std::thread(renderPixels, &img, &cam);

		for (auto& t : threads)
			t.join();
	}
	else
	{
		renderPixels(&img, &cam);
	}

	img.saveBMP();

	std::cout << "\a";
}

void renderPixels(Image* img, Camera* cam)
{
	Ray ray;
	ray.m_pos.x = 0.0f;

	float y, z, u, v;
	int img_width = img->x;
	float dz = 1.0f / float(img_width);

	size_t pixelIndex = ++currentPixelIndex;
	const size_t nrPixels = img_width * img_width;

	while (pixelIndex < nrPixels)
	{
		// caluclate the pixel world coordinates
		u = (pixelIndex % img_width);
		v = (pixelIndex / img_width);
		z = ((u / float(img_width)) * 2.0f - 1.0f) + dz;
		y = ((v / float(img_width)) * 2.0f - 1.0f) + dz;

		ray.m_pos.y = y;
		ray.m_pos.z = z;

		ray.m_dir = glm::normalize(ray.m_pos - cam->m_pos);

		PixelRGB pixelColor = L_in(&ray);

		img->imgData.r[pixelIndex] = pixelColor.m_r;
		img->imgData.g[pixelIndex] = pixelColor.m_g;
		img->imgData.b[pixelIndex] = pixelColor.m_b;

		pixelIndex = ++currentPixelIndex;
	}
}

PixelRGB L_in(Ray* ray)
{
	RayIntersectionData iD;
	iD.m_material.m_diffuse.m_r = 0.0f;
	iD.m_material.m_diffuse.m_g = 0.0f;
	iD.m_material.m_diffuse.m_b = 0.0f;

	findClosestIntersection(ray, &iD);

	glm::vec3 inLight = glm::vec3(0.0f);
	for (int i = 0; i < D_RAYS_PER_PIXEL; i++) 
	{
		inLight += L_out(&iD, ray);
	}
	inLight /= glm::vec3(float(D_RAYS_PER_PIXEL));

	PixelRGB pixelColor{ inLight.r, inLight.g, inLight.b };
	return pixelColor;
}

glm::vec3 L_out(RayIntersectionData* inData, Ray* ray)
{
	glm::vec3 inEmmissive = glm::vec3(inData->m_material.m_emmisive.m_r, inData->m_material.m_emmisive.m_g, inData->m_material.m_emmisive.m_b);
	glm::vec3 inDiffuse = glm::vec3(inData->m_material.m_diffuse.m_r, inData->m_material.m_diffuse.m_g, inData->m_material.m_diffuse.m_b);
	glm::vec3 surfaceNormal = inData->m_normal;
	float albedo = inData->m_material.albedo;

	if (inEmmissive != glm::vec3(0.0f))
	{
		return inEmmissive;
	}

	glm::vec3 directLight = shadowRay(inData);

	glm::vec3 indirectLight = inEmmissive;

	float u = getRandomFloat();
	if (u < D_RAY_LAUNCH_PROBABILITY)
	{
		// randomize ray direction
		Ray newRay;
		newRay.m_dir = uniformSampleHemisphere(surfaceNormal);

		// move the new ray position a small amount away from the intersection to 
		// avoid self intersection
		newRay.m_pos = inData->m_intersectionPoint + glm::vec3(D_EPSILON) * newRay.m_dir;

		// calculate the rendering eq
		RayIntersectionData data;

		if (findClosestIntersection(&newRay, &data))
			indirectLight +=  (albedo / D_RAY_LAUNCH_PROBABILITY) * L_out(&data, &newRay) * inDiffuse * glm::dot(newRay.m_dir, surfaceNormal);

		return directLight + indirectLight;
	}
	else
	{
		return directLight + indirectLight;
	}
}

bool findClosestIntersection(Ray* ray, RayIntersectionData* intersectionData)
{
	bool intersected = false;
	for (const auto& t : c_triangles)
		intersected |= rayIntersection(&t, ray, intersectionData);

	for (const auto& s : c_spheres)
		intersected |= rayIntersection(&s, ray, intersectionData);

	return intersected;
}

bool perfectReflectedRay(Ray* ray, RayIntersectionData* intersectionData)
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

	intersectionData->m_material.m_diffuse.m_r = reflectedRayIntersection.m_material.m_diffuse.m_r;
	intersectionData->m_material.m_diffuse.m_g = reflectedRayIntersection.m_material.m_diffuse.m_g;
	intersectionData->m_material.m_diffuse.m_b = reflectedRayIntersection.m_material.m_diffuse.m_b;

	return true;
}

glm::vec3 shadowRay(RayIntersectionData* intersectionData)
{
	static glm::vec3 lightNormal = glm::vec3(0.0f, -1.0f, 0.0f);
	static PixelRGB notLit = { 0.0f, 0.0f, 0.0f };
	static int sizeOfTri = c_triangles.size();

	glm::vec3 directLightSum = glm::vec3(0.0f);
	glm::vec3 diffuse = glm::vec3(intersectionData->m_material.m_diffuse.m_r, 
		intersectionData->m_material.m_diffuse.m_g, 
		intersectionData->m_material.m_diffuse.m_b);

	glm::vec3 intersection = intersectionData->m_intersectionPoint;
	glm::vec3 surfaceNormal = intersectionData->m_normal;

	for (int lIndex = 0; lIndex < 2; ++lIndex)
	{
		const Triangle* light = &(c_triangles.at(sizeOfTri - 1 - lIndex));

		for (int i = 0; i < C_MAX_SHADOWRAYS; ++i)
		{
			// find random point on area light
			float u = 0.0f;
			float v = 0.0f;
			do {
				u = getRandomFloat();
				v = getRandomFloat();
			} while (u + v > 1.0f);

			// constuct the point using barycentric coordinates
			glm::vec3 q = (1 - u - v) * light->m_a + u * light->m_b + v * light->m_c;

			glm::vec3 q_i = q - intersection;

			Ray ray;
			ray.m_dir = glm::normalize(q_i);
			ray.m_pos = intersection + ray.m_dir * D_EPSILON;

			// if the surface normal shadow ray points in different directions or are orthogonal
			// it is not lit by the point on the area light considered
			float dot = glm::dot(ray.m_dir, surfaceNormal);
			if (dot > D_EPSILON)
			{
				RayIntersectionData shadowRayIntersection;
				//TODO: These two assignments might not be needed test and remove
				shadowRayIntersection.m_time = -10000.0f;
				shadowRayIntersection.m_intersectionPoint = glm::vec3(1000.0f, 1000.0f, 1000.0f);
				findClosestIntersection(&ray, &shadowRayIntersection);

				float shadowRayLength = glm::length(shadowRayIntersection.m_intersectionPoint - intersection);
				float q_iLength = glm::length(q_i);

				if (shadowRayLength >= q_iLength - 0.01f)
				{
					// TODO: rewrite this code to more general such that a light normal doesnt have to be 0, -1, 0
					float beta = glm::dot(-q_i, lightNormal) / q_iLength;
					float alpha = glm::dot(q_i, surfaceNormal) / q_iLength;

					// calculate the geometric term
					float G = (alpha * beta) / (q_iLength * q_iLength);

					directLightSum += diffuse * G;
				}
			}
		}
	}

	//TODO: L0??? Le is (1.0, 1.0, 1.0) for all light sources not needed?
	directLightSum = directLightSum * (2 * C_LIGHT_AREA / float(C_MAX_SHADOWRAYS));

	return directLightSum;
}
