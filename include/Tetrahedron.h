#pragma once
#include "Entity.h"

class Tetrahedron :
	public Entity
{
public:
	Tetrahedron(float dX, float dY, float dZ );
	~Tetrahedron();
};