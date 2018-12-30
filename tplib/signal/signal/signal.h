#ifndef _TPLIB_SIGNAL_SIGNAL_SIGNAL_H__
#define _TPLIB_SIGNAL_SIGNAL_SIGNAL_H__

template <typename T>
class Signal{
	
	public:
	
		Signal();

		//process in time-domain
		static void preprocess(T &s, int l, int r, double alpha = 0.95);
		
		void setRectangularWindow(int N);
		void setBetaSplinerWindow(int N);
		void setHammingWindow(int N);
		void setBlackmanWindow(int N, double alpha = 0.16);
		void setFlatTopWindow(int N);
		void getWindow(const T &s, T &w, int start, int N) const;
		double getWindowSum(const T &s, int start, int N) const;
		double getWindowAver(const T &s, int start, int N) const;
		
		double getShortTermAverageEnergy(const T &s, int N) const;
		double getShortTermAverageAmplitude(const T &s, int N) const;
		double getShortTermZeroCrossing(const T &s, int N, double A = 0) const;
		
		//process in frequency-domain
		
		 /*
		  * T2 is array of Complex
		  * N is power of 2;
		  * mode = 1: fourier translate;
		  * mode = -1: inverse fourier translate
		  */ 
		template <typename T2>
		void getFrequencyDomain(const T &src, T2 &dst, int N, int mode = 1) const;
		/*
		 * T2 is array of Complex
		 */ 
		template <typename T2>
		void getEnergy(const T2 &src, T &dst, int N) const;
		
		
		//file operation
		int getWavSize(std::string fn) const;
		void printWavInfo(std::string fn) const;
		bool loadWav(T &s, std::string fn, int &N) const;
		void saveWav(const T &s, std::string fn, int N) const;
		
	private:
	
		Block<double> window;
		
		//used in file operation
		static int ByteToInt2(BYTE c0, BYTE c1);
		static int ByteToInt4(BYTE c0, BYTE c1, BYTE c2, BYTE c3);
		static void Int2ToByte(BYTE &c0, BYTE &c1, int x);
		static void Int4ToByte(BYTE &c0, BYTE &c1, BYTE &c2, BYTE &c3, int x);
};

#include "signal_time.cpp"
#include "signal_frequency.cpp"
#include "signal_file.cpp"

#endif