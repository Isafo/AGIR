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
	const int x = 480;
	const int y = 480;

	Color imgData;
};