#ifndef _TPLIB_TPLIB_COMPLEX_COMPLEX_H__
#define _TPLIB_TPLIB_COMPLEX_COMPLEX_H__

class Complex{
	
	public:
	
		double re;
		double im;
	
		Complex();
		Complex(const double &re);
		Complex(const double &re, const double &im);
		Complex(const Complex &c);
		
		static Complex UNIT(double phi);
		
		friend Complex operator + (const Complex &lhs, const Complex &rhs);
		friend Complex operator - (const Complex &lhs, const Complex &rhs);
		friend Complex operator * (const Complex &lhs, const Complex &rhs);
		friend Complex operator / (const Complex &lhs, const Complex &rhs);
		friend bool operator == (const Complex &lhs, const Complex &rhs);
		
		operator double();
		
		Complex conjugate() const;
		Complex reciprocal() const;
		Complex sqrt() const;
		double modulus() const;
		double sqrmod() const;
		double argument() const;
		Complex log() const;
		Complex pow(double n) const;
};

#include "complex.cpp"

#endif