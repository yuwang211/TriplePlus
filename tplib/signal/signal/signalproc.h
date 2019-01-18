#ifndef _TPLIB_SIGNAL_SIGNAL_SIGNALPROC_H__
#define _TPLIB_SIGNAL_SIGNAL_SIGNALPROC_H__


class SignalProc{
	
	public:

		//process in time-domain
        template<typename T>
		static void preprocess(T &s, int l, int r, double alpha = 0.95);
		
        //generate window function filter sequence
        template<typename T>
		static void genRectangularWindow(T &s, int N);
    
        template<typename T>
		static void genBetaSplinerWindow(T &s, int N);
    
        template<typename T>
		static void genHammingWindow(T &s, int N);
    
        template<typename T>
		static void genBlackmanWindow(T &s, int N, double alpha = 0.16);
    
        template<typename T>
		static void genFlatTopWindow(T &s, int N);
    
        //windows filter
        template<typename T>
		static void getWindow(const T &s, const T &w, T &t, int start, int N, double alpha = 1.0);
    
        template<typename T>
		static double getWindowSum(const T &s, const T &w, int start, int N);
    
        template<typename T>
		static double getWindowAver(const T &s, const T &w, int start, int N);
		
        //signal analysis
        template<typename T>
		static double getShortTermAverageEnergy(const T &s, int N);
    
        template<typename T>
		static double getShortTermAverageAmplitude(const T &s, int N);
    
        template<typename T>
		static double getShortTermZeroCrossing(const T &s, int N, double A = 0);
		
		//process in frequency-domain
		
		 /*
		  * T2 is array of Complex
		  * N is power of 2;
		  * mode = 1: fourier translate;
		  * mode = -1: inverse fourier translate
		  */ 
		template <typename T, typename T2>
		static void getFrequencyDomain(const T &src, T2 &dst, int N, int mode = 1);
    
        /*
         * T2 is array of Complex
         */
        template <typename T, typename T2>
        static void getEnergy(const T2 &src, T &dst, int N);
    
        template <typename T, typename T2>
        static void getWeight(const T2 &src, T &dst, int N);
		
		//file operation
		static int getWavSize(std::string fn);
		static void printWavInfo(std::string fn);
    
        template<typename T>
		static bool loadWav(T &s, std::string fn, int &N);
    
        template<typename T>
		static void saveWav(const T &s, std::string fn, int N);
    
		
	private:
	
		//Block<double> window;
		
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
