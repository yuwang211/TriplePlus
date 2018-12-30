#ifndef _TPLIB_BITMAP_COLOR_COLOR_CPP__
#define _TPLIB_BITMAP_COLOR_COLOR_CPP__

const Color Color::clBlack  = Color(0, 0, 0);
const Color Color::clWhite  = Color(255, 255, 255);
const Color Color::clRed    = Color(255,   0,   0);
const Color Color::clGreen  = Color(  0, 255,   0);
const Color Color::clBlue   = Color(  0,   0, 255);
const Color Color::clCyan   = Color(  0, 255, 255);
const Color Color::clPink   = Color(255,   0, 255);
const Color Color::clYellow = Color(255, 255,   0);
const Color Color::clGray   = Color(127, 127, 127);

bool operator == (const Color &a, const Color &b)
{
	return a.R == b.R && a.G == b.G && a.B == b.B;
}

bool operator != (const Color &a, const Color &b)
{
	return a.R != b.R || a.G != b.G || a.B != b.B;
}

int Color::distance(Color b)
{
	return 3 * Sqr(R - b.R) + 4 * Sqr(G - b.G) + 2 * Sqr(B - b.B);
}


#endif