#include "Tetrahedron.h"

Tetrahedron::Tetrahedron(float dX, float dY, float dZ) {
	nverts = 12;
	ntris = 4;

	float vertex_array_data[] = {
		-dX / 2.0f, -dY / 2.0f,  dZ / 2.0f,			0.0f, -1.0f, 0.0f,
		dX / 2.0f,  -dY / 2.0f,  dZ / 2.0f,			0.0f, -1.0f, 0.0f,
		0.0f,		-dY / 2.0f, -dZ / 2.0f,			0.0f, -1.0f, 0.0f,

		-dX / 2.0f, -dY / 2.0f,		dZ / 2.0f,		0.0f, 0.5f, 0.5f,	// 3
		dX / 2.0f,  -dY / 2.0f,		dZ / 2.0f,		0.0f, 0.5f, 0.5f,
		0.0f,	 	 dY / 2.0f,		0.0f,			0.0f, 0.5f, 0.5f,

		dX / 2.0f,  -dY / 2.0f,  dZ / 2.0f,			0.5f, 0.5f, 0.0f,	// 6
		0.0f,		-dY / 2.0f, -dZ / 2.0f,			0.5f, 0.5f, 0.0f,
		0.0f,		 dY / 2.0f,  0.0f,				0.5f, 0.5f, 0.0f,

		-dX / 2.0f, -dY / 2.0f,  dZ / 2.0f,			-0.5f, 0.5f, 0.0f,  // 9
		0.0f,		-dY / 2.0f, -dZ / 2.0f,			-0.5f, 0.5f, 0.0f,
		0.0f,		 dY / 2.0f,	 0.0f,				-0.5f, 0.5f, 0.0f,
	};

	verts.x = new float[nverts];
	verts.y = new float[nverts];
	verts.z = new float[nverts];

	// save the data in the vertices SoA
	// TODO: should i save the normals? unless remove them from vertex_array_data. Make sure the memory access is linear
	for (int i = 0; i < nverts * 6; i = i + 6)
	{
		verts.x[i / 6] = vertex_array_data[i];
		verts.y[i / 6] = vertex_array_data[i + 1];
		verts.z[i / 6] = vertex_array_data[i + 2];
	}

	static const int index_array_data[] = {
		0, 2, 1,
		3, 4, 5,
		6, 7, 8,
		10, 9, 11
	};

	// save the indices
	indices = new int[ntris * 3];
	for (int i = 0; i < ntris * 3; i++)
	{
		indices[i] = index_array_data[i];
	}
}