#ifndef FUNCTYPE_CPP
#define FUNCTYPE_CPP


FuncNum::FuncNum(double x):a(x), b(x)
{
}

FuncNum::FuncNum(double a, double b):a(a), b(b)
{
}

FuncNum FuncNum::add(FuncNum y)
{
    return FuncNum(a + y.a, b + y.b);
}

FuncNum FuncNum::sub(FuncNum y)
{
    return FuncNum(a - y.b, b - y.a);
}

FuncNum FuncNum::mul(FuncNum y)
{
    return FuncNum(a * y.a, b * y.b);
}

FuncNum FuncNum::div(FuncNum y)
{
    if (y.a <= 0 && 0 <= y.b)
        return FuncNum(-INF, INF);
    else if (y.b < 0)
        return FuncNum(a / y.b, b / y.a);
    else
        return FuncNum(a / y.a, b / y.b);
}

FuncNum FuncNum::max_(FuncNum y)
{
    return FuncNum(fmax(a, y.a), fmax(b, y.b));
}

FuncNum FuncNum::min_(FuncNum y)
{
    return FuncNum(fmin(a, y.a), fmin(b, y.b));
}

FuncNum FuncNum::sqrt_()
{
    return FuncNum(sqrt(a), sqrt(b));
}

FuncNum FuncNum::sin_()
{
	double k;
	if (a >= 0)
		k = -(int)(a / (2 * PI)) * 2 * PI;
	else
		k = (int)(-(a + EPS) / (2 * PI) + 1) * 2 * PI;
	a += k;
	b += k;
	double na = fmin(sin(a), sin(b)) - EPS;
	if (a < 1.5 * PI && 1.5 * PI < b)
		na = -1;
	if (a < 3.5 * PI && 3.5 * PI < b)
		na = -1;
	double nb = fmax(sin(a), sin(b)) + EPS;
	if (a < 0.5 * PI && 0.5 * PI < b)
		nb = 1;
	if (a < 2.5 * PI && 2.5 * PI < b)
		nb = 1;
	
    return FuncNum(na, nb);
}

FuncNum FuncNum::cos_()
{
    return add(FuncNum(0.5 * PI)).sin_();
}

FuncBool FuncNum::ge(FuncNum y)
{
    return FuncBool(a > y.b - EPS, b > y.a + EPS);
}

FuncBool FuncNum::le(FuncNum y)
{
    return FuncBool(b < y.a + EPS, a < y.b + EPS);
}

FuncBool FuncNum::eq(FuncNum y)
{
    if (a > y.b + EPS || b < y.a - EPS) return FuncBool(false, false);
    else return FuncBool(false, true);
}

FuncBool::FuncBool(bool x):a(x), b(x)
{
}

FuncBool::FuncBool(bool a,bool b):a(a), b(b)
{
}


void FuncPic::draw(Bitmap &bmp, int X, int Y)
{
    x0_ = -10;
    y0_ = -10;
    x1_ = 10;
    y1_ = 10;
    X_ = X;
    Y_ = Y;
    bmp.fillRect(0, 0, X,  Y , Color::clBlue);
    paint(bmp, 0, 0, X - 1, Y - 1, 9);
}

FuncBool FuncPic::getBool(double y0, double x0, double y1, double x1)
{
    FuncNum x(x0, x1);
    FuncNum y(y0, y1);
    FuncNum sinx(x.sin_());
    FuncNum siny(y.sin_());
    return sinx.add(y).min_(x.add(siny)).cos_().cos_().sub(
           siny.add(x).max_(y.add(sinx)).sin_().cos_()).ge(FuncNum(0));
    //return y.eq(x.sin_());
	
}

void paintRect(Bitmap &bmp, int x0, int y0, int x1, int y1, Color c)
{
	for (int i = x0; i <= x1; ++i)
	for (int j = y0; j <= y1; ++j)
		bmp.putPixel(i, j, c);
}

void FuncPic::paint(Bitmap &bmp, int X0, int Y0, int X1, int Y1, int dep)
{
	//printf("!%d %d %d %d\n", X0, Y0, X1, Y1);
    FuncBool b = getBool(x0_ + (x1_ - x0_) * (double)X0 / (double)X_,
                         y0_ + (y1_ - y0_) * (double)Y0 / (double)Y_,
                         x0_ + (x1_ - x0_) * (double)(X1 + 1) / (double)X_,
                         y0_ + (y1_ - y0_) * (double)(Y1 + 1) / (double)Y_);
    if (b.isTrue())
    {
        paintRect(bmp, X0, Y0 , X1, Y1, Color::clBlack);
    }
    else if (b.isFalse())
    {
        paintRect(bmp, X0, Y0 , X1, Y1, Color::clWhite);
    }
	else if (((X0 == X1) && (Y0 == Y1)) || (dep == 0))
	{
        //paintRect(bmp, X0, Y0 , X1, Y1, Color::clBlack);
	}
    else
    {
        int XM = (X0 + X1) / 2;
        int YM = (Y0 + Y1) / 2;
        paint(bmp, XM + 1, Y0, X1, YM, dep - 1);
        paint(bmp, X0, YM + 1, XM, Y1, dep - 1);
        paint(bmp, XM + 1, YM + 1, X1, Y1, dep - 1);
        paint(bmp, X0, Y0, XM, YM, dep - 1);
    }
}

#endif