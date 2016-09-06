#pragma once
#include "Entity.h"
class Sphere : public Entity {
public:
	
	// Creates a sphere  
	Sphere(float _rad);
	~Sphere();

	Sphere() {
		nverts = 0;
		ntris = 0;
	};

	void createSphere(float radius, int segments);

	float getRadius(){return radius;}

private:
	int nverts; // Number of vertices in the vertex array
	int ntris;  // Number of triangles in the index array (may be zero)

	float radius;
};