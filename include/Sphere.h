#pragma once
#include "Entity.h"
class Sphere : public Entity {
public:
	
	// Creates a sphere  
	Sphere(float _rad);
	~Sphere();

	void createSphere(float radius, int segments);
	float getRadius(){ return radius; }

private:
	float radius;
};