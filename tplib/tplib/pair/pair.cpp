#ifndef _TPLIB_TPLIB_PAIR_PAIR_CPP__
#define _TPLIB_TPLIB_PAIR_PAIR_CPP__


template <typename T0, typename T1>
inline Pair<T0, T1> MakePair(const T0 &x, const T1 &y) 
{
	return Pair<T0, T1>(x, y);
}

template <typename T0, typename T1>
inline bool operator == (const Pair<T0, T1> &x, const Pair<T0, T1> &y)
{
	return x.x == y.x && x.y == y.y;
}

template <typename T0, typename T1>
inline bool operator < (const Pair<T0, T1> &x, const Pair<T0, T1> &y) 
{
	return x.x == y.x ? x.y < y.y :x.x < y.x;
}

#endif