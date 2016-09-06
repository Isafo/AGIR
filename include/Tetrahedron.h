#pragma once
#include "Entity.h"

class Tetrahedron :
	public Entity
{
public:
	Tetrahedron()
	{
		nverts = 0;
		ntris = 0;
	};

	Tetrahedron(float dX, float dY, float dZ );
	~Tetrahedron() = default;

private:
	int nverts; // Number of vertices in the vertex array
	int ntris;  // Number of triangles in the index array (may be zero)

};