#ifndef _TPLIB_TPLIB_USECNT_USECNT_CPP__
#define _TPLIB_TPLIB_USECNT_USECNT_CPP__


Usecnt::Usecnt()
{
	p = new int(1);
}

Usecnt::Usecnt(const Usecnt &u): p(u.p) 
{
	++*p;
}

Usecnt::~Usecnt()
{
	if (--*p == 0) delete p;
}
		
bool Usecnt::only()
{
	return *p == 1;
}

bool Usecnt::makeonly()
{
	if (*p == 1) return false;
	--*p;
	p = new int(1);
	return true;
}
		
bool Usecnt::reattach(const Usecnt &u)
{
	++*u.p;
	if (--*p == 0)
	{
		delete p;
		p = u.p;
		return true;
	}
	else
	{
		p = u.p;
		return false;
	}
}

#endif