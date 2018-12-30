#ifndef _TPLIB_TPLIB_BIT_BIT_H__
#define _TPLIB_TPLIB_BIT_BIT_H__

class Bit{
	
	public:
		static int lowbit(int x);
		static int countOne(int x);
		static int inverse(int x);
		static int inverse(int x, int len);
		static bool isOneBit(int x);
		static int position(int x);
	
};

#include "bit.cpp"

#endif