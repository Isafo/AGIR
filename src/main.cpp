#include <emmintrin.h>

#include "Image.h"
#include "Plane.h"
#include "Sphere.h"
#include "Hexagon.h"
#include "Tetrahedron.h"

#define M_PI 3.14159265358979323846
#define EPSILON 0.000001


struct Vertices {
	float* x;
	float* y;
	float* z;
};

// TODO: what more info is needed about entities? Is the struct really needed?
struct EntityInfo {
	double Color[3];
};

struct TransformData {
	float translation[3];
	//float minAabb[3];
	//float maxAabb[3];
	float scale; // uniform scaling
	float rotation;
};

struct Rays {
	Vertices* start;
	Vertices* end;
	int* triangleIndex; // index to intersecting triangle
};

int main()
{
	Image img;
	img.saveBMP();

	Plane bigWall(10.0f, 10.0f);
	Plane smallWall(6.71f, 10.0f);
	Sphere sphere(1.0f);
	Hexagon hexagon();
	Tetrahedron tertahedron(1.0f, 1.0f, 1.0f);

	// TODO: rewrite this in a cleaner way
	// floor and roof
	TransformData hexagonTransforms[2];
	hexagonTransforms[0].translation[0] = { 0.0f };
	hexagonTransforms[0].translation[1] = { -5.0f };
	hexagonTransforms[0].translation[2] = { -0.0f };
	hexagonTransforms[0].rotation = M_PI; // x-axis
	hexagonTransforms[0].scale = 1.0f;

	hexagonTransforms[1].translation[0] = { 0.0f };
	hexagonTransforms[1].translation[1] = { 5.0f };
	hexagonTransforms[1].translation[2] = { 0.0f };
	hexagonTransforms[1].rotation = 0.0f; // x-axis
	hexagonTransforms[1].scale = 1.0f;

	// walls
	TransformData bigWallTransforms[2];
	bigWallTransforms[0].translation[0] = { 5.0f };
	bigWallTransforms[0].translation[1] = { 0.0f };
	bigWallTransforms[0].translation[2] = { -6.0f };
	bigWallTransforms[0].rotation = 0.0f; // y-axis
	bigWallTransforms[0].scale = 1.0f;

	bigWallTransforms[1].translation[0] = { 5.0f };
	bigWallTransforms[1].translation[1] = { 0.0f };
	bigWallTransforms[1].translation[2] = { 6.0f };
	bigWallTransforms[1].rotation = M_PI; // y-axis
	bigWallTransforms[1].scale = 1.0f;

	// angled walls
	TransformData smallWallTransforms[4];
	smallWallTransforms[0].translation[0] = { -1.5f};
	smallWallTransforms[0].translation[1] = { 0.0f};
	smallWallTransforms[0].translation[2] = { -3.0f };
	smallWallTransforms[0].rotation = 1.1071;
	smallWallTransforms[0].scale = 1.0f;

	smallWallTransforms[1].translation[0] = { -1.5f };
	smallWallTransforms[1].translation[1] = { 0.0f };
	smallWallTransforms[1].translation[2] = { 3.0f };
	smallWallTransforms[1].rotation = M_PI - 1.1071;
	smallWallTransforms[1].scale = 1.0f;

	smallWallTransforms[2].translation[0] = { 11.5f };
	smallWallTransforms[2].translation[1] = { 0.0f };
	smallWallTransforms[2].translation[2] = { -3.0f };
	smallWallTransforms[2].rotation = -1.1071;
	smallWallTransforms[2].scale = 1.0f;

	smallWallTransforms[3].translation[0] = { 11.5f };
	smallWallTransforms[3].translation[1] = { 0.0f };
	smallWallTransforms[3].translation[2] = { 3.0f };
	smallWallTransforms[3].rotation = M_PI + 1.1071;
	smallWallTransforms[3].scale = 1.0f;
}

void triangleIntersection(Entity* entities, Rays* rays, unsigned int nrEntities, 
	unsigned int nrRays)
{
	__m128 _0x4 = _mm_set1_ps(0.0f);

	for (int i_ent = 0; i_ent < nrEntities; ++i_ent)
	{
		int offset = 0;

		for (int i_tri = 0; i_tri < entities[i_ent].ntris; ++i_tri)
		{
			// get the vertices
			float V0x = entities[i_ent].verts.x[entities[i_ent].indices[i_tri + offset]];
			float V0y = entities[i_ent].verts.y[entities[i_ent].indices[i_tri + offset]];
			float V0z = entities[i_ent].verts.z[entities[i_ent].indices[i_tri + offset]];
			++offset;

			float V1x = entities[i_ent].verts.x[entities[i_ent].indices[i_tri + offset]];
			float V1y = entities[i_ent].verts.y[entities[i_ent].indices[i_tri + offset]];
			float V1z = entities[i_ent].verts.z[entities[i_ent].indices[i_tri + offset]];
			++offset;

			float V2x = entities[i_ent].verts.x[entities[i_ent].indices[i_tri + offset]];
			float V2y = entities[i_ent].verts.y[entities[i_ent].indices[i_tri + offset]];
			float V2z = entities[i_ent].verts.z[entities[i_ent].indices[i_tri + offset]];
			++offset;

			// calculate two triangle edges
			__m128 e1_xxxx = _mm_set1_ps(V1x - V0x);
			__m128 e1_yyyy = _mm_set1_ps(V1y - V0y);
			__m128 e1_zzzz = _mm_set1_ps(V1z - V0z);

			__m128 e2_xxxx = _mm_set1_ps(V2x - V0x);
			__m128 e2_yyyy = _mm_set1_ps(V2y - V0y);
			__m128 e2_zzzz = _mm_set1_ps(V2z - V0z);
			
			// test intersection with the rays
			// TODO: look at this for loop condition once decided how to handle non-first rays
			for (int i_ray = 0; i_ray < nrRays / 4; ++i_ray)
			{
				__m128 rayStart_xxxx = ((__m128*)(rays->start->x))[i_ray];
				__m128 rayStart_yyyy = ((__m128*)(rays->start->y))[i_ray];
				__m128 rayStart_zzzz = ((__m128*)(rays->start->z))[i_ray];

				__m128 rayEnd_xxxx = ((__m128*)(rays->end->x))[i_ray];
				__m128 rayEnd_yyyy = ((__m128*)(rays->end->y))[i_ray];
				__m128 rayEnd_zzzz = ((__m128*)(rays->end->z))[i_ray];
			
				__m128 rayDir_xxxx = _mm_sub_ps(rayEnd_xxxx, rayStart_xxxx);
				__m128 rayDir_yyyy = _mm_sub_ps(rayEnd_yyyy, rayStart_yyyy);
				__m128 rayDir_zzzz = _mm_sub_ps(rayEnd_zzzz, rayStart_zzzz);
				
				// cross prod D x e2
				__m128 P_xxxx = _mm_sub_ps(_mm_mul_ps(rayDir_yyyy, e2_zzzz), _mm_mul_ps(rayDir_zzzz, e2_yyyy));
				__m128 P_yyyy = _mm_sub_ps(_mm_mul_ps(rayDir_xxxx, e2_zzzz), _mm_mul_ps(rayDir_zzzz, e2_xxxx));
				__m128 P_zzzz = _mm_sub_ps(_mm_mul_ps(rayDir_xxxx, e2_yyyy), _mm_mul_ps(rayDir_yyyy, e2_xxxx));

				// e1 dot P
				__m128 dotE1P_0123 = vecMulAdd(e1_xxxx, P_xxxx, _0x4);
				dotE1P_0123 = vecMulAdd(e1_yyyy, P_yyyy, dotE1P_0123);
				dotE1P_0123 = vecMulAdd(e1_xxxx, P_xxxx, dotE1P_0123);

			}
		}
	}
}

__m128 vecMulAdd(__m128 a, __m128 b, __m128 c)
{
	return _mm_add_ps(_mm_mul_ps(a, b), c);
}