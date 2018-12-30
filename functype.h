#ifndef FUNCTYPE_H
#define FUNCTYPE_H

#include <cmath>

#define TPIMPORT_BITMAP
#define TPIMPORT_MATRIX
#include "tplib/tplib.h"

using namespace tplib;

class FuncNum;
class FuncBool;

class FuncNum{
    public:

        FuncNum(double x = 0);
        FuncNum(double a, double b);

        FuncNum add(FuncNum y);
        FuncNum sub(FuncNum y);
        FuncNum mul(FuncNum y);
        FuncNum div(FuncNum y);

        FuncNum max_(FuncNum y);
        FuncNum min_(FuncNum y);

        FuncNum sqrt_();
        FuncNum sin_();
        FuncNum cos_();

        FuncBool ge(FuncNum y);
        FuncBool le(FuncNum y);
        FuncBool eq(FuncNum y);

    private:
        static constexpr double INF = 1E+30;
        static constexpr double EPS = 1E-80;
        static constexpr double PI = 3.1415936535;
        double a, b;

};

class FuncBool{
public:

    FuncBool(bool x = 0);
    FuncBool(bool a, bool b);

    bool isTrue() { return a && b; }
    bool isFalse() { return !a && !b;}

private:
    bool a, b;
};


class FuncPic{
    public:
        void draw(Bitmap &bmp, int X, int Y);

    private:

        double x0_, y0_, x1_, y1_;
        double X_, Y_;

        FuncBool getBool(double x0, double y0, double x1, double y1);
        void paint(Bitmap &bmp, int X0, int Y0, int X1, int Y1, int dep = 65536);

};


#include "functype.cpp"


#endif // FUNCTYPE_H
