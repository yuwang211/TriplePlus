#ifndef _TPLIB_BITMAP_COLOR_COLOR_H__
#define _TPLIB_BITMAP_COLOR_COLOR_H__

class Color{
	public:
	
		int B, G, R; //[0, 255]
		
		Color() {}
		Color(BYTE R, BYTE G, BYTE B) : R(R), G(G), B(B) {}
		
		static const Color clBlack;
		static const Color clWhite;
		static const Color clRed;
		static const Color clGreen;
		static const Color clBlue;
		static const Color clCyan;
		static const Color clPink;
		static const Color clYellow;
		static const Color clGray;
		
		static const int MAX_COLOR_DISTANCE = 255 * 255 * 9;
		int distance(Color b);
};

bool operator == (const Color &a, const Color &b);
bool operator != (const Color &a, const Color &b);

#include "color.cpp"

#endif