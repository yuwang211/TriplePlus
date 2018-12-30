#ifndef _TPLIB_TPLIB_TPL_CPP__
#define _TPLIB_TPLIB_TPL_CPP__

template <typename T> void Swap(T &arg0, T &arg1) { T tmp = arg0; arg0 = arg1; arg1 = tmp; }
template <typename T> T Max(const T &arg0, const T &arg1) { return arg0 > arg1 ? arg0 : arg1; }
template <typename T> T Min(const T &arg0, const T &arg1) { return arg0 < arg1 ? arg0 : arg1; }
template <typename T> T Abs(const T &arg0) { return arg0 >= 0 ? arg0 : -arg0; }
template <typename T> int Sgn(const T &arg0) { return arg0 >= 0 ? (arg0 > 0 ? 1 : 0) : -1; }
template <> int Sgn<double>(const double &arg0) { return arg0 > -(1E-8) ? (arg0 > (1E-8) ? 1 : 0) : -1; }
template <typename T> T Sqr(const T &arg0) { return arg0 * arg0; }


inline double Rand()
{
	Assert(RAND_MAX == 32767, "rand() setting is different, please do not use this function");
	long long x = (((long long)(rand())) << 37) ^ 
					(((long long)(rand())) << 30) ^
					(((long long)(rand())) << 15) ^
					(((long long)(rand())) <<  0) ^  
					0x3ff0000000000000LL;
	return *((double *)(&x)) - 1;
}


#endif