#include "Image.h"
#include "Plane.h"
#include "Sphere.h"
#include "Hexagon.h"
#include "Tetrahedron.h"

#define M_PI 3.14159265358979323846

struct Vertices {
	float* x;
	float* y;
	float* z;
};

// TODO: what more info is needed about entities? Is the struct really needed?
struct EntityInfo {
	double Color[3];
};

struct TransformData {
	//float rotation[4];
	float translation[3];
	//float minAabb[3];
	//float maxAabb[3];
	float scale; // uniform scaling
	float rotation; // need to understand quaternions and rewrite this
};

struct Rays {
	Vertices* start;
	Vertices* end;
	int* triangleIndex; // index to intersecting triangle
};

int main()
{
	Image img;
	img.saveBMP();

	Plane bigWall(10.0f, 10.0f);
	Plane smallWall(6.71f, 10.0f);
	Sphere sphere(1.0f);
	Hexagon hexagon();
	Tetrahedron tertahedron(1.0f, 1.0f, 1.0f);

	// TODO: rewrite this in a cleaner way
	// floor and roof
	TransformData hexagonTransforms[2];
	hexagonTransforms[0].translation[0] = { 0.0f };
	hexagonTransforms[0].translation[1] = { -5.0f };
	hexagonTransforms[0].translation[2] = { -0.0f };
	hexagonTransforms[0].rotation = M_PI; // x-axis
	hexagonTransforms[0].scale = 1.0f;

	hexagonTransforms[1].translation[0] = { 0.0f };
	hexagonTransforms[1].translation[1] = { 5.0f };
	hexagonTransforms[1].translation[2] = { 0.0f };
	hexagonTransforms[1].rotation = 0.0f; // x-axis
	hexagonTransforms[1].scale = 1.0f;

	// walls
	TransformData bigWallTransforms[2];
	bigWallTransforms[0].translation[0] = { 5.0f };
	bigWallTransforms[0].translation[1] = { 0.0f };
	bigWallTransforms[0].translation[2] = { -6.0f };
	bigWallTransforms[0].rotation = 0.0f; // y-axis
	bigWallTransforms[0].scale = 1.0f;

	bigWallTransforms[1].translation[0] = { 5.0f };
	bigWallTransforms[1].translation[1] = { 0.0f };
	bigWallTransforms[1].translation[2] = { 6.0f };
	bigWallTransforms[1].rotation = M_PI; // y-axis
	bigWallTransforms[1].scale = 1.0f;

	// angled walls
	TransformData smallWallTransforms[4];
	smallWallTransforms[0].translation[0] = { -1.5f};
	smallWallTransforms[0].translation[1] = { 0.0f};
	smallWallTransforms[0].translation[2] = { -3.0f };
	smallWallTransforms[0].rotation = 1.1071;
	smallWallTransforms[0].scale = 1.0f;

	smallWallTransforms[1].translation[0] = { -1.5f };
	smallWallTransforms[1].translation[1] = { 0.0f };
	smallWallTransforms[1].translation[2] = { 3.0f };
	smallWallTransforms[1].rotation = M_PI - 1.1071;
	smallWallTransforms[1].scale = 1.0f;

	smallWallTransforms[2].translation[0] = { 11.5f };
	smallWallTransforms[2].translation[1] = { 0.0f };
	smallWallTransforms[2].translation[2] = { -3.0f };
	smallWallTransforms[2].rotation = -1.1071;
	smallWallTransforms[2].scale = 1.0f;

	smallWallTransforms[3].translation[0] = { 11.5f };
	smallWallTransforms[3].translation[1] = { 0.0f };
	smallWallTransforms[3].translation[2] = { 3.0f };
	smallWallTransforms[3].rotation = M_PI + 1.1071;
	smallWallTransforms[3].scale = 1.0f;
	
}
