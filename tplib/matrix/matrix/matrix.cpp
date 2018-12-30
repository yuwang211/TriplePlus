inline void Matrix::setindex()
{
	double *d = num->begin();
	for (int i = 0; i < row; ++i)
	{
		(*index)[i] = d;
		d += col;
	}
}

inline void Matrix::makeonly()
{
	if (uc.makeonly())
	{
		Block<double> *tmp = num;
		num = new Block<double>(row * col);
		Assert(num, "malloc failed");
		index = new Block<pdouble>(row);
		Assert(index, "mallow failed");
		memcpy(num->begin(), tmp->begin(), row * col * sizeof(double));
		setindex();
	}
}

Matrix::Matrix(): row(0), col(0)
{
	num = NULL;
	index = NULL;
}

Matrix::Matrix(int r, int c): row(r), col(c)
{
	num = new Block<double>(r * c);
	Assert(num, "malloc failed");
	index = new Block<pdouble>(r);
	Assert(index, "mallow failed");
	num->reset();
	setindex();
}

Matrix::Matrix(const Matrix &m): uc(m.uc), row(m.row), col(m.col)
{
	index = m.index;
	num = m.num;
}

Matrix::Matrix(int n, double *d, int direction)
{
	if (direction == VERTICAL)
	{
		row = 1;
		col = n;
		num = new Block<double>(n);
		Assert(num, "malloc failed");
		index = new Block<pdouble>(1);
		Assert(index, "mallow failed");
		memcpy(num->begin(), d, n * sizeof(double));
		setindex();
	}
	else if (direction == HORIZON)
	{
		row = n;
		col = 1;
		num = new Block<double>(n);
		Assert(num, "malloc failed");
		index = new Block<pdouble>(n);
		Assert(index, "mallow failed");
		memcpy(num->begin(), d, n * sizeof(double));
		setindex();
	}
	else if (direction == DIAGONAL)
	{
		row = n;
		col = n;
		num = new Block<double>(n * n);
		Assert(num, "malloc failed");
		index = new Block<pdouble>(n);
		Assert(index, "mallow failed");
		setindex();
		double *dd = num->begin();
		double *s = d;
		for (int i = 0; i < n; ++i)
		{
			(*dd) = (*(s++));
			dd += (n + 1);
		}
	}
}

Matrix::~Matrix()
{
	if (uc.only())
	{
		delete index;
		delete num;
	}
}

Matrix& Matrix::operator=(const Matrix &m)
{
	if (uc.reattach(m.uc))
	{
		delete index;
		delete num;
	}
	row = m.row;
	col = m.col;
	index = m.index;
	num = m.num;
	return *this;
}

Matrix Matrix::Make(int r, int c, ...)
{
	int count = r * c;
	printf("count = %d\n", count);
	Matrix ret(r, c);
	va_list ap;
	va_start(ap, c);
	for (int i = 0; i < r; ++i)
		for (int j = 0; j < c; ++j)
			ret[i][j] = va_arg(ap, double);
	va_end(ap);
	return ret;
}

Matrix Matrix::Zero(int r, int c)
{
	return Matrix(r, c);
}

Matrix Matrix::Identity(int n)
{
	Matrix ret(n, n);
	double *d = ret.num->begin();
	for (int i = 0; i < n; ++i)
	{
		(*d) = 1.0;
		d += (n + 1);
	}
	return ret;
}

Matrix Matrix::Random(int n, int m)
{
	Matrix ret(n, m);
	double *d = ret.num->begin();
	for (int i = n * m; i > 0; --i)
	{
		(*(d++)) = Rand();
	}
	return ret;
}

inline void Matrix::update()
{
	makeonly();
}

inline double* Matrix::operator[] (int k)
{
	update();
	return (*index)[k];
}

inline double& Matrix::elem(int x, int y)
{
	Assert(0 <= x < row && 0 <= y < col, "matrix index exceeded");
	Assert(!uc.makeonly(), "please use update() before modify this matrix");
	return (*index)[x][y];
}

inline const double* Matrix::operator[] (int k) const
{
	return (*index)[k];
}

Matrix operator + (const Matrix &lhs, const Matrix &rhs)
{
	Assert(lhs.row == rhs.row && lhs.col == rhs.col, "matrix size not matched");
	Matrix ret(lhs);
	ret.update();
	double *s = ret.num->begin();
	double *d = rhs.num->begin();
	for (int i = rhs.col * rhs.row; i > 0; --i)
		(*(s++)) += (*(d++));
	return ret;
}

Matrix operator - (const Matrix &lhs, const Matrix &rhs)
{
	Assert(lhs.row == rhs.row && lhs.col == rhs.col, "matrix size not matched");
	Matrix ret(lhs);
	ret.update();
	double *s = ret.num->begin();
	double *d = rhs.num->begin();
	for (int i = rhs.col * rhs.row; i > 0; --i)
		(*(s++)) -= (*(d++));
	return ret;
}

Matrix operator * (const Matrix &lhs, const Matrix &rhs)
{
	Assert(lhs.col == rhs.row, "matrix size not matched");
	
	if (lhs.row == lhs.col && rhs.col == rhs.row && lhs.row >= Matrix::FAST_MULTIPLE_SIZE)
	{
		Matrix l;
		Matrix r;
		if (lhs.row & 1)
		{
			l = ((lhs | Matrix(lhs.row, 1)) & Matrix(1, lhs.col + 1));
			r = ((rhs | Matrix(rhs.row, 1)) & Matrix(1, rhs.col + 1));
		}
		else
		{
			l = lhs;
			r = rhs;
		}
		int n = l.row;
		int n2 = (n >> 1);
		Matrix A11(l.submatrix( 0,  0, n2, n2));
		Matrix A12(l.submatrix( 0, n2, n2,  n));
		Matrix A21(l.submatrix(n2,  0,  n, n2));
		Matrix A22(l.submatrix(n2, n2,  n,  n));
		Matrix B11(r.submatrix( 0,  0, n2, n2));
		Matrix B12(r.submatrix( 0, n2, n2,  n));
		Matrix B21(r.submatrix(n2,  0,  n, n2));
		Matrix B22(r.submatrix(n2, n2,  n,  n));
		Matrix S1(B12 - B22);
		Matrix S2(A11 + A12);
		Matrix S3(A21 + A22);
		Matrix S4(B21 - B11);
		Matrix S5(A11 + A22);
		Matrix S6(B11 + B22);
		Matrix S7(A12 - A22);
		Matrix S8(B21 + B22);
		Matrix S9(A11 - A21);
		Matrix S0(B11 + B12);
		Matrix P1(A11 * S1);
		Matrix P2(S2 * B22);
		Matrix P3(S3 * B11);
		Matrix P4(A22 * S4);
		Matrix P5(S5 * S6);
		Matrix P6(S7 * S8);
		Matrix P7(S9 * S0);
		
		Matrix ret(((P5 + P4 - P2 + P6) | (P1 + P2)) & ((P3 + P4) | (P5 + P1 - P3 - P7)));
		if (lhs.row == l.row) return ret;
		else                  return ret.submatrix(0, 0, lhs.row, lhs.col);
	}
	
	
	Matrix ret(lhs.row, rhs.col);
	
	for (int i = 0; i < lhs.row; ++i)
	for (int j = 0; j < rhs.row; ++j)
	for (int k = 0; k < rhs.col; ++k)
		ret.elem(i, k) += lhs[i][j] * rhs[j][k];
	return ret;
}

Matrix operator * (const Matrix &lhs, double rhs)
{
	Matrix ret(lhs);
	ret.update();
	double *s = ret.num->begin();
	for (int i = lhs.col * lhs.row; i > 0; --i)
		(*(s++)) *= rhs;
	return ret;
}

Matrix operator * (double lhs, const Matrix &rhs)
{
	Matrix ret(rhs);
	ret.update();
	double *s = ret.num->begin();
	for (int i = rhs.col * rhs.row; i > 0; --i)
		(*(s++)) *= lhs;
	return ret;
}

Matrix operator & (const Matrix &lhs, const Matrix &rhs)
{
	Assert(lhs.col == rhs.col, "matrix size not matched");
	Matrix ret(lhs.row + rhs.row, rhs.col);
	
	memcpy(ret.num->begin(), lhs.num->begin(), lhs.row * lhs.col * sizeof(double));
	memcpy(ret.num->begin() + lhs.row * lhs.col, rhs.num->begin(), rhs.row * rhs.col * sizeof(double));
		
	return ret;
}

Matrix operator | (const Matrix &lhs, const Matrix &rhs)
{
	Assert(lhs.row == rhs.row, "matrix size not matched");
	Matrix ret(lhs.row, lhs.col + rhs.col);
	
	for (int i = 0; i < ret.row; ++i)
	{
		memcpy((*(ret.index))[i], (*(lhs.index))[i], lhs.col * sizeof(double));
		memcpy((*(ret.index))[i] + lhs.col, (*(rhs.index))[i], rhs.col * sizeof(double));
	}
	
	return ret;
}

int Matrix::gauss(Matrix &m, int mode)
{
	Assert(row == m.row, "matrix size not matched");
	update();
	m.update();
	double d;
	gauss_swap = 0;
	for (int i = 0; i < row; ++i)
	{
		int l = i;
		for (int j = i + 1; j < row; ++j)
		if (fabs((*index)[j][i]) > fabs((*index)[l][i]))
			l = j;
			
		if (l != i) ++gauss_swap;
			
		if (fabs((*index)[l][i]) < EPS)
			return i;
		
		for (int j = 0; j < col; ++j)
		{
			d = (*index)[l][j];
			(*index)[l][j] = (*index)[i][j];
			(*index)[i][j] = d;
		}
		for (int j = 0; j < m.col; ++j)
		{
			d = m[l][j];
			m.elem(l, j) = m[i][j];
			m.elem(i, j) = d;
		}
		
		for (int j = i + 1; j < row; ++j)
		{
			d = (*index)[j][i] / (*index)[i][i];
			for (int k = 0; k < col; ++k)
				(*index)[j][k] -= d * (*index)[i][k];
			for (int k = 0; k < m.col; ++k)
				m.elem(j, k) -= d * m.elem(i, k);
		}
	}
	
	if (mode == GAUSS_UPPER) return row;
	
	for (int i = row - 1; i >= 0; --i)
	{
		for (int j = i - 1; j >= 0; --j)
		{
			d = (*index)[j][i] / (*index)[i][i];
			for (int k = 0; k < m.col; ++k)
				m.elem(j, k) -= d * m.elem(i, k);
			(*index)[j][i] = 0.0;
		}
	}
	
	if (mode == GAUSS_DIAGONAL) return row;
	
	for (int i = 0; i < row; ++i)
	{
		d = 1.0 / (*index)[i][i];
		for (int k = 0; k < m.col; ++k)
			m.elem(i, k) *= d;
		(*index)[i][i] = 1.0;
	}
	
	return row;
}

int Matrix::rank() const
{
	Matrix m(*this);
	Matrix tmp(row, 0);
	return m.gauss(tmp, GAUSS_UPPER);
}

double Matrix::det() const
{
	Assert(row == col, "matrix size not matched");
	Matrix m(*this);
	Matrix tmp(row, 0);
	m.gauss(tmp, GAUSS_UPPER);
	double ret = 1.0;
	for (int i = 0; i < row; ++i)
		ret *= m.elem(i, i);
	if (m.gauss_swap & 1) return -ret;
	else                  return ret;
}

double Matrix::trace() const
{
	Assert(row == col, "matrix size not matched");
	double ret = 0;
	for (int i = 0; i < row; ++i)
		ret += (*index)[i][i];
	return ret;
}

Matrix Matrix::transpose() const
{
	Matrix ret(col, row);
	for (int i = 0; i < row; ++i)
	for (int j = 0; j < col; ++j)
		ret.elem(j, i) = (*index)[i][j];
	return ret;
}

Matrix Matrix::Inverse() const
{
	Assert(row == col, "matrix size not matched");
	Debug(Matrix tmp);
	Assert((*this).Invertible(tmp), "matrix is not invertible");
	Matrix m(*this);
	Matrix ret(Matrix::Identity(row));
	m.gauss(ret, GAUSS_UNIT);
	return ret;
}

bool Matrix::Invertible(Matrix &m) const
{
	Matrix tmp(*this);
	m = Identity(row);
	return (tmp.gauss(m, GAUSS_UNIT) == row);
}

Matrix Matrix::submatrix(int x0, int y0, int x1, int y1) const
{
	Assert(x0 < x1 && y0 < y1, "illegal matrix size");
	Assert(x1 <= row && y1 <= col, "matrix index exceed");
	Matrix ret(x1 - x0, y1 - y0);
	for (int i = 0; i < ret.row; ++i)
	for (int j = 0; j < ret.col; ++j)
		ret.elem(i, j) = (*index)[x0 + i][y0 + j];
	return ret;
}

double Matrix::max() const
{
	double ret = (*index)[0][0];
	for (int i = 0; i < row; ++i)
	for (int j = 0; j < col; ++j)
		ret = Max(ret, (*index)[i][j]);
	return ret;
}

double Matrix::min() const
{
	double ret = (*index)[0][0];
	for (int i = 0; i < row; ++i)
	for (int j = 0; j < col; ++j)
		ret = Min(ret, (*index)[i][j]);
	return ret;
}

double Matrix::sum() const
{
	double ret = 0;
	for (int i = 0; i < row; ++i)
	for (int j = 0; j < col; ++j)
		ret += (*index)[i][j];
	return ret;
}

double Matrix::mean() const
{
	double ret = 0;
	for (int i = 0; i < row; ++i)
	for (int j = 0; j < col; ++j)
		ret += (*index)[i][j];
	return ret / (double)(row * col);
}

double Matrix::var() const
{
	double mean = 0;
	for (int i = 0; i < row; ++i)
	for (int j = 0; j < col; ++j)
		mean += (*index)[i][j];
	mean /= (double)(row * col);
	double ret = 0;
	for (int i = 0; i < row; ++i)
	for (int j = 0; j < col; ++j)
		ret += Sqr((*index)[i][j] - mean);
	
	return ret / (double)(row * col);
}

double Matrix::std() const
{
	double mean = 0;
	for (int i = 0; i < row; ++i)
	for (int j = 0; j < col; ++j)
		mean += (*index)[i][j];
	mean /= (double)(row * col);
	double ret = 0;
	for (int i = 0; i < row; ++i)
	for (int j = 0; j < col; ++j)
		ret += Sqr((*index)[i][j] - mean);
	
	return sqrt(ret / (double)(row * col));
}

Matrix Matrix::prefixsum() const
{
	Matrix ret(*this);
	ret.update();
	for (int i = 1; i < row; ++i)
		ret[i][0] += ret[i - 1][0];
	for (int j = 1; j < col; ++j)
		ret[0][j] += ret[0][j - 1];
	for (int i = 1; i < row; ++i)
		for (int j = 1; j < col; ++j)
			ret[i][j] += ret[i - 1][j] + ret[i][j - 1] - ret[i - 1][j - 1];
	return ret;
}

Matrix Matrix::func(Func0 f) const
{
	Matrix ret(*this);
	ret.update();
	for (double *i = ret.num->begin(); i != ret.num->end(); ++i)
		*i = (*f)();
	return ret;
}

Matrix Matrix::func(Func1 f) const
{
	Matrix ret(*this);
	ret.update();
	for (double *i = ret.num->begin(); i != ret.num->end(); ++i)
		*i = (*f)(*i);
	return ret;
}

Matrix Matrix::func(Func2 f) const
{
	Matrix ret(*this);
	ret.update();
	double *d = ret.num->begin();
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
			*(d++) = (*f)(i, j);
	return ret;
}

Matrix Matrix::func(Func3 f) const
{
	Matrix ret(*this);
	ret.update();
	double *d = ret.num->begin();
	for (int i = 0; i < row; ++i)
		for (int j = 0; j < col; ++j)
		{
			*(d) = (*f)(i, j, (*d));
			++d;
		}
	return ret;
}
