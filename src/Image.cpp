#include "Image.h"
#include <iostream>

#include "glm/glm.hpp"

Image::Image()
{
	imgData.r = new float[x * y];
	imgData.g = new float[x * y];
	imgData.b = new float[x * y];
}

Image::~Image()
{
	delete[] imgData.r;
	delete[] imgData.g;
	delete[] imgData.b;
}


void Image::saveBMP()
{
	//save image
	unsigned char *img = NULL;
	int filesize = 54 + 3 * x*y;
	if (img)
		free(img);
	img = (unsigned char *)malloc(3 * x*y);
	memset(img, 0, sizeof(img));

	float r; float g; float b; float gr; float gg; float gb; float tr; float tg; float tb;
	int iX;
	int iY;

	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			iX = j; iY = (y - 1) - i;
			tr = imgData.r[i * y + j];
			tg = imgData.g[i * y + j];
			tb = imgData.b[i * y + j];
			if (tr > 1.0f) tr = 1.0f;
			if (tg > 1.0f) tg = 1.0f;
			if (tb > 1.0f) tb = 1.0f;
			gr = glm::pow(tr, 0.4f);
			gg = glm::pow(tg, 0.4f);
			gb = glm::pow(tb, 0.4f);
			r = gr * 255;
			g = gg * 255;
			b = gb * 255;
			img[(iX + iY*x) * 3 + 2] = (unsigned char)(r);
			img[(iX + iY*x) * 3 + 1] = (unsigned char)(g);
			img[(iX + iY*x) * 3 + 0] = (unsigned char)(b);
		}
	}

	unsigned char bmpfileheader[14] = { 'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0 };
	unsigned char bmpinfoheader[40] = { 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0 };
	unsigned char bmppad[3] = { 0, 0, 0 };

	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);

	bmpinfoheader[4] = (unsigned char)(x);
	bmpinfoheader[5] = (unsigned char)(x >> 8);
	bmpinfoheader[6] = (unsigned char)(x >> 16);
	bmpinfoheader[7] = (unsigned char)(x >> 24);
	bmpinfoheader[8] = (unsigned char)(y);
	bmpinfoheader[9] = (unsigned char)(y >> 8);
	bmpinfoheader[10] = (unsigned char)(y >> 16);
	bmpinfoheader[11] = (unsigned char)(y >> 24);

	FILE *f;
	f = fopen("img.bmp", "wb");
	fwrite(bmpfileheader, 1, 14, f);
	fwrite(bmpinfoheader, 1, 40, f);
	for (int i = 0; i<y; i++)
	{
		fwrite(img + (x*(y - i - 1) * 3), 3, x, f);
		fwrite(bmppad, 1, (4 - (x * 3) % 4) % 4, f);
	}
	fclose(f);
	std::cout << "Image has been saved." << std::endl;
}