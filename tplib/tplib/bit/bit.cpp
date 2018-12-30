#ifndef _TPLIB_TPLIB_BIT_BIT_CPP__
#define _TPLIB_TPLIB_BIT_BIT_CPP__

inline int Bit::lowbit(int x)
{
	return x & -x;
}

inline int Bit::countOne(int x)
{
	x = (x & 0x55555555) + ((x >> 1) & 0x55555555); 
	x = (x & 0x33333333) + ((x >> 2) & 0x33333333); 
	x = (x & 0x0F0F0F0F) + ((x >> 4) & 0x0F0F0F0F); 
	x = (x & 0x00FF00FF) + ((x >> 8) & 0x00FF00FF); 
	x = (x & 0x0000FFFF) + ((x >> 16) & 0x0000FFFF);
	return x;
}

inline int Bit::inverse(int x)
{
	x = ((x & 0x55555555) << 1) | ((x & 0xAAAAAAAA) >> 1);
	x = ((x & 0x33333333) << 2) | ((x & 0xCCCCCCCC) >> 2);
	x = ((x & 0x0F0F0F0F) << 4) | ((x & 0xF0F0F0F0) >> 4);
	x = ((x & 0x00FF00FF) << 8) | ((x & 0xFF00FF00) >> 8);
	x = ((x & 0x0000FFFF) << 16) | ((x & 0xFFFF0000) >> 16);
	return x;
}

inline int Bit::inverse(int x, int len)
{
	return (inverse(x) >> (32 - len)) & ((1 << len) - 1);
}

inline bool Bit::isOneBit(int x)
{
	return x == lowbit(x);
}

inline int Bit::position(int x)
{
	int t = 0;
	if ((x >> 16) > 0) {x >>= 16; t += 16;}
	if ((x >> 8) > 0) {x >>= 8; t += 8;}
	if ((x >> 4) > 0) {x >>= 4; t += 4;}
	if ((x >> 2) > 0) {x >>= 2; t += 2;}
	if ((x >> 1) > 0) {x >>= 1; t += 1;}
	return t;
}

#endif