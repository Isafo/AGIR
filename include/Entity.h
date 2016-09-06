#pragma once
#include <cstdlib>

#include <stdlib.h>
#include <math.h> 

class Entity
{
protected:
	struct Vertices
	{
		float* x;
		float* y;
		float* z;
	};

public:
	Vertices verts;
	int* indices;
	int nverts; // Number of vertices
	int ntris;  // Number of triangles

	virtual ~Entity() = 0;

};