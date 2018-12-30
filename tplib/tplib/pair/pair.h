#ifndef _TPLIB_TPLIB_PAIR_PAIR_H__
#define _TPLIB_TPLIB_PAIR_PAIR_H__

template <typename T1, typename T2>
class Pair{
	
	public:
		
		T1 x;
		T2 y;
		
		Pair() {}
		Pair(const Pair<T1, T2> &p) : x(p.x), y(p.y) {}
		Pair(const T1 &x, const T2 &y) : x(x), y(y) {}
		
};

template <typename T0, typename T1>
inline Pair<T0, T1> MakePair(const T0 &x, const T1 &y); 

template <typename T0, typename T1>
inline bool operator == (const Pair<T0, T1> &x, const Pair<T0, T1> &y);

template <typename T0, typename T1>
inline bool operator < (const Pair<T0, T1> &x, const Pair<T0, T1> &y);

#include "pair.cpp"

#endif