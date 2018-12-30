#ifndef _TPLIB_BITMAP_BITMAP_BITMAP_CPP__
#define _TPLIB_BITMAP_BITMAP_BITMAP_CPP__

void Bitmap::create(int height, int width)
{
	biWidth = width;
	biHeight = height;
	padding = (4 - ((3 * biWidth) % 4)) % 4;
	biWidthSize = biWidth * 3 + padding;
	biSizeImage = biHeight * biWidthSize;
	bfSize = biSizeImage + 54;
	if (pixel != NULL) delete []pixel;
	pixel = new BYTE[biSizeImage];
	memset(pixel, 0, biSizeImage);
}

void Bitmap::clone(const Bitmap &src)
{
	create(src.biHeight, src.biWidth);
	memcpy(pixel, src.pixel, biSizeImage);
}

bool Bitmap::legal(int x, int y)
{
	if (pixel == NULL) return false;
	return (0 <= x) && (x < biHeight) && (0 <= y) && (y < biWidth);
}

#endif