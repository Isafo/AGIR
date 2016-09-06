#include "Hexagon.h"

Hexagon::Hexagon(float x, float y, float z)
{
	nverts = 7;
	ntris = 6;

	float vertex_array_data[] = {
		//		Vertex						Normals	
		-3.0f + x,  y,    0.0f + z,			 0.0f, 1.0f, 0.0f,
		0.0f,		y,	 -6.0f + z,			 0.0f, 1.0f, 0.0f,
		10.0f + x,	y,	 -6.0f + z,			 0.0f, 1.0f, 0.0f,
		13.0f + x,	y,	  0.0f + z,			 0.0f, 1.0f, 0.0f,
		10.0f + x,	y,	  6.0f + z,			 0.0f, 1.0f, 0.0f,
		0.0 + x,	y,	  6.0f + z,			 0.0f, 1.0f, 0.0f,
		5.0f + x,	y,	  0.0f + z,			 0.0f, 1.0f, 0.0f,
	};

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
		0, 1, 6,
		1, 2, 6,

		2, 3, 6,
		3, 4, 6,

		4, 5, 6,
		5, 0, 6,
	};

	// save the indices
	indices = new int[ntris * 3];
	for (int i = 0; i < ntris * 3; i++)
	{
		indices[i] = index_array_data[i];
	}
}

Hexagon::~Hexagon()
{
	delete[] indices;
	delete[] verts.x;
	delete[] verts.y;
	delete[] verts.z;
}