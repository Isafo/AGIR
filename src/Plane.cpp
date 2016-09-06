#include "Plane.h"

Plane::Plane(float dX, float dY)
{
	float vertex_array_data[] = {
		//			Vertex						Normals
		-dX / 2.0f, -dY / 2.0f,  0.0f,		 0.0f, 0.0f, 1.0f,
		 dX / 2.0f,	-dY / 2.0f,	 0.0f,	     0.0f, 0.0f, 1.0f,
		 dX / 2.0f,	 dY / 2.0f,	 0.0f,		 0.0f, 0.0f, 1.0f,
		-dX / 2.0f,	 dY / 2.0f,  0.0f,		 0.0f, 0.0f, 1.0f,
	};

	nverts = 4;
	ntris = 2;

	// TODO: allocate a large buffer to save the data in. Dont want fragmented data
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
		0, 1, 2,
		0, 2, 3
	};

	// save the indices
	indices = new int[ntris * 3];
	for (int i = 0; i < ntris * 3; i++)
	{
		indices[i] = index_array_data[i];
	}
}

Plane::~Plane() 
{
	delete[] indices;
	delete[] verts.x;
	delete[] verts.y;
	delete[] verts.z;
}