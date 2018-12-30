#ifndef _TPLIB_BITMAP_BITMAP_DRAW_DRAW_cpp__
#define _TPLIB_BITMAP_BITMAP_DRAW_DRAW_cpp__

Color Bitmap::getPixel(int x, int y)
{
	if (y < 0 || y >= biWidth || x < 0 || x >= biHeight)
	{
		return Color::clBlack;
	}
	int cur = (x * biWidthSize + y * 3);
	return Color(pixel[cur + 2], pixel[cur + 1], pixel[cur]);
}

void Bitmap::putPixel(int x, int y, Color c)
{
	if (y < 0 || y >= biWidth || x < 0 || x >= biHeight)
	{
		return;
	}
	int cur = (x * biWidthSize + y * 3);
	pixel[cur + 2] = c.R;
	pixel[cur + 1] = c.G;
	pixel[cur + 0] = c.B;
}

void Bitmap::drawLine(int x1, int y1, int x2, int y2, Color c)
{
	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int dx2 = dx * 2;
	int dy2 = dy * 2;
	int cx = x2 > x1 ? 1 : -1;
	int cy = y2 > y1 ? 1 : -1;
	int x = x1;
	int y = y1;
	if (dx > dy)
	{
		int e = -dx;
		for (int i = 0; i <= dx; ++i)
		{
			putPixel(x, y, c);
			x += cx;
			e += dy2;
			if (e >= 0)
			{
				y += cy;
				e -= dx2;
			}
		}
	}
	else
	{
		int e = -dy;
		for (int i = 0; i <= dy; ++i)
		{
			putPixel(x, y, c);
			y += cy;
			e += dx2;
			if (e >= 0)
			{
				x += cx;
				e -= dy2;
			}
		}
	}
	//if (x != x2 || y != y1) printf("ERROR\n");
}

void Bitmap::drawBLine(int x1, int y1, int x2, int y2, Color c, int b)
{
	drawLine(x1, y1, x2, y2, c);
	if (b == 0) return;
	int dx = (y2 - y1) > 0 ? 1 : -1;
	int dy = (x2 - x1) > 0 ? -1 : 1;
	if (abs(y2 - y1) > abs(x2 - x1))dy = 0;
	else dx = 0;
	for (int i = 1; i <= b; ++i)
	{
		drawLine(x1 + dx * i, y1 + dy * i, 
				 x2 + dx * i, y2 + dy * i, c);
		drawLine(x1 - dx * i, y1 - dy * i, 
				 x2 - dx * i, y2 - dy * i, c);
	}
	if (b > 1)
	{
		fillCircle(x1, y1, b - 1, c);
		fillCircle(x2, y2, b - 1, c);
	}
}

void Bitmap::drawHorizontal(int x, int y1, int y2, Color c)
{
	int l = Max(0, x * biWidthSize + y1 * 3);
	int r = Min(biSizeImage, x * biWidthSize + y2 * 3 + 3);
	for (int cur = l; cur < r; cur += 3)
	{
		pixel[cur + 2] = c.R;
		pixel[cur + 1] = c.G;
		pixel[cur + 0] = c.B;
	}
}

void Bitmap::drawVertical(int x1, int x2, int y, Color c)
{
	int l = Max(0, x1 * biWidthSize + y * 3);
	int r = Min(biSizeImage, x2 * biWidthSize + y * 3 + 3);
	for (int cur = l; cur < r; cur += biWidthSize)
	{
		pixel[cur + 2] = c.R;
		pixel[cur + 1] = c.G;
		pixel[cur + 0] = c.B;
	}
}

void Bitmap::drawRect(int x1, int y1, int x2, int y2, Color c)
{
	drawVertical(x1, x2, y1, c);
	drawVertical(x1, x2, y2, c);
	drawHorizontal(x1, y1, y2, c);
	drawHorizontal(x2, y1, y2, c);
}

void Bitmap::fillRect(int x1, int y1, int x2, int y2, Color c)
{
	for (int i = x1; i < x2; ++i)
		drawHorizontal(i, y1, y2, c);
}

void Bitmap::drawCircle_8_(int x0, int y0, int x, int y, Color c)
{
	putPixel(x0 + x, y0 + y, c);
	putPixel(x0 + x, y0 - y, c);
	putPixel(x0 - x, y0 + y, c);
	putPixel(x0 - x, y0 - y, c);
	putPixel(x0 + y, y0 + x, c);
	putPixel(x0 + y, y0 - x, c);
	putPixel(x0 - y, y0 + x, c);
	putPixel(x0 - y, y0 - x, c);
}

void Bitmap::drawCircle(int x0, int y0, int r, Color c)
{
	int x = 0;
	int y = r;
	int d = 3 - 2 * r;
	while (x <= y)
	{
		drawCircle_8_(x0, y0, x, y, c);
		if (d < 0)
			d += (x << 2) + 6;
		else
		{
			d += ((x - y) << 2) + 10;
			--y;
		}
		++x;
	}
	drawCircle_8_(x0, y0, x, y, c);
}

void Bitmap::fillCircle(int x0, int y0, int r, Color c)
{
	int x = 0;
	int y = r;
	int d = 3 - 2 * r;
	int yi;
	while (x <= y)
	{
		for(yi = x; yi <= y; ++yi)
			drawCircle_8_(x0, y0, x, yi, c);
		if (d < 0)
			d += (x << 2) + 6;
		else
		{
			d += ((x - y) << 2) + 10;
			--y;
		}
		++x;
	}
	drawCircle_8_(x0, y0, x, y, c);
}

void Bitmap::drawEllipse_4_(int x0, int y0, int x, int y, Color c)
{
	putPixel(x0 + x, y0 + y, c);
	putPixel(x0 + x, y0 - y, c);
	putPixel(x0 - x, y0 + y, c);
	putPixel(x0 - x, y0 - y, c);
}

void Bitmap::drawEllipse(int x0, int y0, int a, int b, Color c)
{
	int sqa = a * a;
	int sqb = b * b;
	int x = 0;
	int y = b;
	int d = (sqb << 1) - (b * sqa << 1) + sqa;
	drawEllipse_4_(x0, y0, x, y, c);
	int P_x = (int)((double)sqa / sqrt((double)(sqa + sqb)) + 0.5);
	while (x <= P_x)
	{
		if (d < 0)
			d += 2 * sqb * (2 * x + 3);
		else
		{
			d += 2 * sqb * (2 * x + 3) - 4 * sqa * (y - 1);
			--y;
		}
		++x;
		drawEllipse_4_(x0, y0, x, y, c);
	}
	d = sqb * (x * x + x) + sqa * (y * y - y) - sqa * sqb;
	while (y >= 0)
	{
		--y;
		if (d < 0)
		{
			++x;
			d += - 2 * sqa * y - sqa + 2 * sqb * x + 2 * sqb;
		}
		else
			d += -2 * sqa * y - sqa;
		drawEllipse_4_(x0, y0, x, y, c);
	}
}

void Bitmap::fillArea(int x, int y, Color c, double d)
{
	int di = (int)(d * d * Color::MAX_COLOR_DISTANCE + 0.5);
	Color midc = getPixel(x, y);
	int *qx = new int[biHeight * biWidth];
	int *qy = new int[biHeight * biWidth];
	BYTE *chk = new BYTE[biHeight * biWidth];
	memset(chk, 0, biHeight * biWidth);
	int open = -1;
	int closed = 0;
	qx[0] = x;
	qy[0] = y;
	chk[x * biWidth + y] = 1;
	int kx, ky, tx, ty;
	while (open < closed)
	{
		kx = qx[++open];
		ky = qy[open];
		for (int i = 0; i < 4; ++i)
		{
			tx = kx + DIRECTION[i][0];
			ty = ky + DIRECTION[i][1];
			if (tx < 0 || tx >= biWidth || ty < 0 || ty >= biHeight ||
			     chk[tx * biWidth + ty]) continue;
			if (midc.distance(getPixel(tx, ty)) > di) 
			{
				//How fuck was I when I debugged these code
				//if (getPixel(tx, ty) != clWhite) printf("fuck\n");
				continue;
			}
			chk[tx * biWidth + ty] = 1;
			qx[++closed] = tx;
			qy[closed] = ty;
		}
	}
	
	for (int i = 0; i <= closed; ++i)
		putPixel(qx[i], qy[i], c);
	
	/*for (int i = 0; i < biHeight; ++i)
	for (int j = 0; j < biWidth; ++j)
		if (chk[i * biWidth + j])
			putPixel(i, j, c);*/
	delete [] qx;
	delete [] qy;
	delete [] chk;
}

void Bitmap::fillTriangle(int x0, int y0, int x1, int y1, int x2, int y2, Color c)
{
	int a = Max(biHeight, biWidth);
	int x[3], y[3];
	if (y0 <= y1 && y0 <= y2)
	{
		x[0] = x0; y[0] = y0;
		if (y1 <= y2)
			x[1] = x1, y[1] = y1, x[2] = x2, y[2] = y2;
		else
			x[1] = x2, y[1] = y2, x[2] = x1, y[2] = y1;
	}
	else if (y1 <= y0 && y1 <= y2)
	{
		x[0] = x1; y[0] = y1;
		if (y0 <= y2)
			x[1] = x0, y[1] = y0, x[2] = x2, y[2] = y2;
		else
			x[1] = x2, y[1] = y2, x[2] = x0, y[2] = y0;
	}
	else if (y2 <= y0 && y2 <= y1)
	{
		x[0] = x2; y[0] = y2;
		if (y0 <= y1)
			x[1] = x0, y[1] = y0, x[2] = x1, y[2] = y1;
		else
			x[1] = x1, y[1] = y1, x[2] = x0, y[2] = y0;
	}
	int yy = Max(y[0], 0);
	int n = 1, lx, rx, tmp;
	double k[3];
	k[0] = (double)(x[2] - x[0]) / (y[2] - y[0]);
	k[1] = (double)(x[1] - x[0]) / (y[1] - y[0]);
	k[2] = (double)(x[2] - x[1]) / (y[2] - y[1]);
	while (yy <= y[2] && yy <= biHeight)
	{
		if (yy > y[n]) ++n;
		lx = (int)(x[n - 1] + 0.5 + (yy - y[n - 1]) * k[n]);
		rx = (int)(x[0] + 0.5 + (yy - y[0]) * k[0]);
		if (lx > rx) tmp = lx, lx = rx, rx = tmp;
		if (rx < 0 || lx >= biWidth) continue;
		if (rx >= biWidth) rx = biWidth - 1;
		if (lx < 0) lx = 0;
		drawVertical(lx, rx, yy, c);
		++yy;
	}
}


#endif
