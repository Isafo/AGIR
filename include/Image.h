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

	const int x = 1000;
	const int y = 1000;

	Color imgData;
};