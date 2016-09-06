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
	~Tetrahedron();
};