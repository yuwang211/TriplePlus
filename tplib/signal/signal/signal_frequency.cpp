#ifndef _TPLIB_SIGNAL_SIGNAL_SIGNAL_FREQUENCY_CPP__
#define _TPLIB_SIGNAL_SIGNAL_SIGNAL_FREQUENCY_CPP__


template <typename T, typename T2>
void SignalProc::getFrequencyDomain(const T &src, T2 &dst, int N, int mode)
{
	for (int i = 0; i < N; ++i) dst[Bit::inverse(i, Bit::position(N))] = src[i];
	for (int i = 2; i <= N; i <<= 1)
	{
		double arc = 2 * PI * mode / (double) i;
		Complex wm(cos(arc), sin(arc));
		for (int k = 0; k < N; k += i)
		{
			Complex w(1, 0);
			for (int j = 0; j * 2 < i; ++j)
			{
				Complex t = w * dst[k + j + i / 2];
				Complex u = dst[k + j];
				dst[k + j] = u + t;
				dst[k + j + i / 2] = u - t;
				w = w * wm;
			}
		}
	}
}

template <typename T,typename T2>
void SignalProc::getWeight(const T2 &src, T &dst, int N)
{
    for (int i = 0; i < N; ++i)
        dst[i] = src[i].modulus();
}

template <typename T,typename T2>
void SignalProc::getEnergy(const T2 &src, T &dst, int N)
{
	for (int i = 0; i < N; ++i)
		dst[i] = Sqr(src[i].modulus());
}



#endif
