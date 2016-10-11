#pragma once

class Image
{
public:
	struct Color
	{
		float* r;
		float* g;
		float* b;
	};

	Image();
	~Image();

	void saveBMP();

	// currently requires x == y
	const int x = 320;
	const int y = 320;

	Color imgData;
};