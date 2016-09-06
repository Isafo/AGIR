#include "Sphere.h"

#define M_PI 3.14159265358979323846

Sphere::Sphere(float _rad)
{
	radius = _rad;
	createSphere(_rad, 32);
}

Sphere::~Sphere()
{
	delete[] indices;
	delete[] verts.x;
	delete[] verts.y;
	delete[] verts.z;
}

void Sphere::createSphere(float radius, int segments) {
	int i, j, base, i0;
	float x, y, z, R;
	double theta, phi;
	int vsegs, hsegs;

	vsegs = segments;
	if (vsegs < 2) vsegs = 2;
	hsegs = vsegs * 2;
	nverts = 1 + (vsegs - 1) * (hsegs + 1) + 1; // top + middle + bottom
	ntris = hsegs + (vsegs - 2) * hsegs * 2 + hsegs; // top + middle + bottom

	verts.x = new float[nverts];
	verts.y = new float[nverts];
	verts.z = new float[nverts];

	indices = new int[ntris * 3];

	// The vertex array: 3D xyz, 3D normal, 2D st (8 floats per vertex)
	// First vertex: top pole (+z is "up" in object local coords)
	verts.x[0] = 0.0f;
	verts.y[0] = 0.0f;
	verts.z[0] = radius;
	//vertexarray[3] = 0.0f;
	//vertexarray[4] = 0.0f;
	//vertexarray[5] = 1.0f;

	// Last vertex: bottom pole
	base = (nverts - 1);
	verts.x[base] = 0.0f;
	verts.y[base] = 0.0f;
	verts.z[base] = -radius;
	//vertexarray[base + 3] = 0.0f;
	//vertexarray[base + 4] = 0.0f;
	//vertexarray[base + 5] = -1.0f;

	// All other vertices:
	// vsegs-1 latitude rings of hsegs+1 vertices each
	// (duplicates at texture seam s=0 / s=1)
	for (j = 0; j<vsegs - 1; j++) { // vsegs-1 latitude rings of vertices
		theta = (double)(j + 1) / vsegs*M_PI;
		z = cos(theta);
		R = sin(theta);
		for (i = 0; i <= hsegs; i++) { // hsegs+1 vertices in each ring (duplicate for texcoords)
			phi = (double)i / hsegs*2.0*M_PI;
			x = R*cos(phi);
			y = R*sin(phi);
			base = (1 + j*(hsegs + 1) + i);
			verts.x[base] = radius*x;
			verts.y[base] = radius*y;
			verts.z[base] = radius*z;
			//vertexarray[base + 3] = x;
			//vertexarray[base + 4] = y;
			//vertexarray[base + 5] = z;
		}
	}

	// The index array: triplets of integers, one for each triangle
	// Top cap
	for (i = 0; i<hsegs; i++) {
		indices[3 * i] = 0;
		indices[3 * i + 1] = 1 + i;
		indices[3 * i + 2] = 2 + i;
	}
	// Middle part (possibly empty if vsegs=2)
	for (j = 0; j<vsegs - 2; j++) {
		for (i = 0; i<hsegs; i++) {
			base = 3 * (hsegs + 2 * (j*hsegs + i));
			i0 = 1 + j*(hsegs + 1) + i;
			indices[base] = i0;
			indices[base + 1] = i0 + hsegs + 1;
			indices[base + 2] = i0 + 1;
			indices[base + 3] = i0 + 1;
			indices[base + 4] = i0 + hsegs + 1;
			indices[base + 5] = i0 + hsegs + 2;
		}
	}
	// Bottom cap
	base = 3 * (hsegs + 2 * (vsegs - 2)*hsegs);
	for (i = 0; i<hsegs; i++) {
		indices[base + 3 * i] = nverts - 1;
		indices[base + 3 * i + 1] = nverts - 2 - i;
		indices[base + 3 * i + 2] = nverts - 3 - i;
	}
};


