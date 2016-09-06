#include "Image.h"
#include "Plane.h"
#include "Sphere.h"

// use SIMD or not? SoA or AoS?
struct Vertices {
	float* x;
	float* y;
	float* z;
};

struct EntityInfo {
	double intensities[3];
};

struct TransformData {
	float rotation[4];
	float scale[3];
	float minAabb[3];
	float maxAabb[3];
};

struct Rays {
	Vertices verts;
	int* triangle; // ptr to intersecting triangle
};

int main(){

	Image img;

	img.saveBMP();

	Plane plane(1.0f, 1.0f);
	Sphere sphere(1.0f);

	return 0;
}