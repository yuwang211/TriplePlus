#ifndef _TPLIB_TPLIB_USECNT_USECNT_H__
#define _TPLIB_TPLIB_USECNT_USECNT_H__


class Usecnt{

	public:
	
		Usecnt();
		Usecnt(const Usecnt &u);
		~Usecnt();
		
		bool only();
		
		bool makeonly();
		
		bool reattach(const Usecnt &u);
		
	private:
	
		int *p;
	
		Usecnt& operator = (const Usecnt&);
		
			
};

#include "usecnt.cpp"

#endif