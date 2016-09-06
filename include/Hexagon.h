#pragma once
#include "Entity.h"

class Hexagon :
	public Entity
{
public:
	Hexagon()
	{
		nverts = 0;
		ntris = 0;
	};

	Hexagon(float x, float y, float z);
	~Hexagon();


private:
	int nverts; // Number of vertices in the vertex array
	int ntris;  // Number of triangles in the index array (may be zero)
};