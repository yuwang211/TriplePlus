#ifndef _TPLIB_TPLIB_COMPLEX_COMPLEX_CPP__
#define _TPLIB_TPLIB_COMPLEX_COMPLEX_CPP__

Complex::Complex(): re(0), im(0)
{
}

Complex::Complex(const double &re): re(re), im(0)
{
}

Complex::Complex(const double &re, const double &im): re(re), im(im)
{
}

Complex::Complex(const Complex &c): re(c.re), im(c.im)
{
}

inline Complex Complex::UNIT(double phi)
{
	return Complex(cos(phi), sin(phi));
}
	
inline Complex operator + (const Complex &lhs, const Complex &rhs)
{
	return Complex(lhs.re + rhs.re, lhs.im + rhs.im);
}

inline Complex operator - (const Complex &lhs, const Complex &rhs)
{
	return Complex(lhs.re - rhs.re, lhs.im - rhs.im);
}

inline Complex operator * (const Complex &lhs, const Complex &rhs)
{
	return Complex(lhs.re * rhs.re - lhs.im * rhs.im,
                   lhs.re * rhs.im + lhs.im * rhs.re);
}

inline Complex operator / (const Complex &lhs, const Complex &rhs)
{
	double d = 1.0 / (rhs.re * rhs.re + rhs.im * rhs.im);
	return Complex(d * (lhs.re * rhs.re + lhs.im * rhs.im),
                   d * (lhs.im * rhs.re - lhs.re * rhs.im));
}

inline bool operator == (const Complex &lhs, const Complex &rhs)
{
	return lhs.re == rhs.re && lhs.im == rhs.im;
}

inline Complex::operator double()
{
	return re;
}

inline Complex Complex::conjugate() const
{
	return Complex(re, -im);
}

inline Complex Complex::reciprocal() const
{
	double d = 1.0 / (re * re + im * im);
	return Complex(d * re, -d * im);
}

inline Complex Complex::sqrt() const
{
	double d = std::sqrt(re * re + im * im);
	return Complex(std::sqrt(0.5 * (d + re)),
				   std::sqrt(0.5 * (d - re)) * Sgn(im));
}

inline double Complex::modulus() const
{
	return std::sqrt(re * re + im * im);
}

inline double Complex::sqrmod() const
{
	return re * re + im * im;
}

inline double Complex::argument() const
{
	return atan2(im, re);
}

inline Complex Complex::log() const
{
	double r = modulus();
	double phi = argument();
	return Complex(std::log(r), phi);
}

inline Complex Complex::pow(double n) const
{
	double r = modulus();
	double phi = argument();
	double len = std::pow(r, phi);
	return Complex(cos(phi) * len, sin(phi) * len);
}

#endif