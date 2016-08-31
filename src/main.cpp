#include "Image.h"

// use SIMD or not? SoA or AoS?
struct Vertices {
	float* x;
	float* y;
	float* z;
};

struct Entity {
	Vertices verts;
	int* indices;
	int nrOfTris;
};

struct EntityInfo {
	double intensities[3];
};

struct TransformData {
	float rotation[4];
	float scale[3];
	float minAabb[3];
	float maxAabb[3];
};

struct Rays {
	Vertices verts;
	int* triangle; // ptr to intersecting triangle
};

void createPlane(Entity* e);

int main(){

	Image img;

	img.saveBMP();

	Entity planeEntity;
	planeEntity.indices = new int[2 * 3];
	planeEntity.verts.x = new float[4];
	planeEntity.verts.y = new float[4];
	planeEntity.verts.z = new float[4];
	planeEntity.nrOfTris = 2;

	createPlane(&planeEntity);


	delete[] planeEntity.indices;
	delete[] planeEntity.verts.x;
	delete[] planeEntity.verts.y;
	delete[] planeEntity.verts.z;

	return 0;
}

inline void createPlane(Entity* e) 
{

	float dX = 1.0f;
	float dZ = 1.0f;

	float vertex_array_data[] = 
	{
		-dX / 2.0f,   0.0f,  -dZ / 2.0f,
		 dX / 2.0f,   0.0f,  -dZ / 2.0f,
		 dX / 2.0f,   0.0f,   dZ / 2.0f,
		-dX / 2.0f,   0.0f,   dZ / 2.0f
	};

	static const int index_array_data[] = 
	{
		2, 1, 0,
		2, 3, 0
	};

	e->nrOfTris = 2;

	for (int i = 0; i < 4; i++) 
	{
		e->verts.x[i] = vertex_array_data[i];
		e->verts.y[i] = vertex_array_data[i + 1];
		e->verts.z[i] = vertex_array_data[i + 2];
	}

	for (int i = 0; i < 6; i++)
	{
		e->indices[i] = index_array_data[i];
	}
}