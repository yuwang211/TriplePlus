#ifndef _TPLIB_TPLIB_TPL_H__
#define _TPLIB_TPLIB_TPL_H__

//debug
#include "assert/assert.h"

//contant
const double PI = 3.14159265358979;

//Type definiation
typedef char CHAR;
typedef unsigned char BYTE;
typedef unsigned short int WORD;
typedef short int SHORTINT;
typedef unsigned int DWORD;
typedef unsigned long long LWORD;
typedef long long INT64;
typedef CHAR *PCHAR;
typedef BYTE *PBYTE;
typedef int *PINT;
typedef void *PVOID;

//Basic function
template <typename T> void Swap(T &arg0, T &arg1);
template <typename T> T Max(const T &arg0, const T &arg1);
template <typename T> T Min(const T &arg0, const T &arg1);
template <typename T> T Abs(const T &arg0);
template <typename T> int Sgn(const T &arg0);
template <> int Sgn<double>(const double &arg0);
template <typename T> T Sqr(const T &arg0);
double Rand();

#include "tpl.cpp"

#include "pair/pair.h"
#include "bit/bit.h"
#include "complex/complex.h"
#include "usecnt/usecnt.h"
#include "block/block.h"



#endif
