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
};