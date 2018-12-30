#ifndef _TPLIB_SIGNAL_SIGNAL_SIGNAL_TIME_CPP__
#define _TPLIB_SIGNAL_SIGNAL_SIGNAL_TIME_CPP__

template <typename T>
Signal<T>::Signal()
{
	
}

template <typename T>
void Signal<T>::preprocess(T &s, int l, int r, double alpha)
{
	for (int i = r - 1; i > l; --i)
		s[i] -= s[i - 1] * alpha;
}

template <typename T>
void Signal<T>::setRectangularWindow(int N)
{
	window.resize(N);
	for (int i = 0; i < N; ++i)
		window[i] = 1;
}

template <typename T>
void Signal<T>::setBetaSplinerWindow(int N)
{
	window.resize(N);
	for (int i = 0; i < N; ++i)
		window[i] = (1 - fabs((i - (N-1)/2)/(N/2)));
}

template <typename T>
void Signal<T>::setHammingWindow(int N)
{
	window.resize(N);
	for (int i = 0; i < N; ++i)
		window[i] = (0.53836 - 0.46164 * cos((2 * PI * i) / (N - 1)));
}

template <typename T>
void Signal<T>::setBlackmanWindow(int N, double alpha)
{
	double alpha0 = (1 - alpha) * 0.5;
	double alpha1 = 0.5;
	double alpha2 = alpha / 2;
	window.resize(N);
	for (int i = 0; i < N; ++i)
		window[i] = (alpha0 - alpha1 * cos((2 * PI * i) / (N - 1))
	                              + alpha2 * cos((4 * PI * i) / (N - 1)));
}

template <typename T>
void Signal<T>::setFlatTopWindow(int N)
{
	double alpha0 = 0.21557895;
	double alpha1 = 0.41663158;
	double alpha2 = 0.277263158;
	double alpha3 = 0.083578947;
	double alpha4 = 0.006947368;
	window.resize(N);
	for (int i = 0; i < N; ++i)
		window[i] = alpha0 - alpha1 * cos((2 * PI * i) / (N - 1))
	                       + alpha2 * cos((4 * PI * i) / (N - 1))
						   - alpha3 * cos((6 * PI * i) / (N - 1))
						   + alpha4 * cos((8 * PI * i) / (N - 1));
}

template <typename T>
void Signal<T>::getWindow(const T &s, T &w, int start, int N) const
{
	for (int i = 0; i < N; ++i)
		w[i] = window[i] * s[i + start];
}

template <typename T>
double Signal<T>::getWindowSum(const T &s, int start, int N) const
{
	double ret = 0;
	for (int i = 0; i < N; ++i)
		ret += window[i] * s[i + start];
	return ret;
}

template <typename T>
double Signal<T>::getWindowAver(const T &s, int start, int N) const
{
	double ret = 0;
	for (int i = 0; i < N; ++i)
		ret += window[i] * s[i + start];
	return ret / (double)N;
}

template <typename T>
double Signal<T>::getShortTermAverageEnergy(const T &s, int N) const
{
	double e = 0;
	for (int i = 0; i < N; ++i)
		e += s[i] * s[i];
	return e;
}

template <typename T>
double Signal<T>::getShortTermAverageAmplitude(const T &s, int N) const
{
	double m = 0;
	for (int i = 0; i < N; ++i)
		m += fabs(s[i]);
	return m;
}

template <typename T>
double Signal<T>::getShortTermZeroCrossing(const T &s, int N, double A) const
{
	double z = 0;
	for (int i = 1; i < N; ++i)
		z += fabs(Sgn(s[i] - A) - Sgn(s[i - 1] - A)) + fabs(Sgn(s[i] + A) - Sgn(s[i - 1] + A));
	return z / (2 * N);
}

#endif