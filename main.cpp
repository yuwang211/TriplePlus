

#include "functype.h"

Bitmap bmp;
FuncPic p;

int main()
{
	bmp.create(1024, 1024);
	p.draw(bmp, 1024, 1024);
	bmp.saveBMP("a.bmp");
	return 0;
}