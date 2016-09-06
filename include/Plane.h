#pragma once
#include "Entity.h"

class Plane :
	public Entity
{
public:
	Plane()
	{
		nverts = 0;
		ntris = 0;
	};

	Plane(float dX, float dZ);
	~Plane();

private:

};