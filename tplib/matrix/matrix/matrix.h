class Matrix{

	public:
	
		static const int VERTICAL = 0;
		static const int HORIZON = 1;
		static const int DIAGONAL = 2;
		
		static const int GAUSS_UPPER = 0;
		static const int GAUSS_DIAGONAL = 1;
		static const int GAUSS_UNIT = 2;
		
		
		typedef double(* Func0)(void);
		typedef double(* Func1)(double);
		typedef double(* Func2)(int, int);
		typedef double(* Func3)(int, int, double);
	
		int row, col;
	
	
		Matrix();
		Matrix(int r, int c);
		Matrix(const Matrix &m);
		Matrix(int n, double *d, int direction = VERTICAL);
		~Matrix();
		
		Matrix& operator=(const Matrix &m);
	
        static Matrix Make(int r, int c, std::initializer_list<double> il);
	
		static Matrix Zero(int r, int c);
		static Matrix Identity(int n);
		static Matrix Random(int n, int m);
		
		void update();
		
		double* operator[] (int k);
		const double* operator[] (int k) const;
		
		double& elem(int x, int y);
		
	
		friend Matrix operator + (const Matrix &lhs, const Matrix &rhs);
		friend Matrix operator - (const Matrix &lhs, const Matrix &rhs);
		friend Matrix operator * (const Matrix &lhs, const Matrix &rhs);
		friend Matrix operator * (const Matrix &lhs, double rhs);
		friend Matrix operator * (double lhs, const Matrix &rhs);
		friend Matrix operator | (const Matrix &lhs, const Matrix &rhs);
		friend Matrix operator & (const Matrix &lhs, const Matrix &rhs);
		
		int gauss(Matrix &m, int mode = GAUSS_UNIT);
		
		int rank() const;
		double det() const;
		double trace() const;
		
		Matrix transpose() const;
		Matrix inverse() const;
		bool invertible(Matrix &m) const;
		Matrix submatrix(int x0, int y0, int x1, int y1) const;
		
		double max() const;
		double min() const;
		double sum() const;
        double sumabs() const;
		double mean() const;
		
		double var() const;
		double std() const;
		
		Matrix prefixsum() const;
    
        double norm(double p) const;
    
        void eigen_greatest(double &lambda, Matrix &v) const;
        void eigen_nearest(double miu, double &lambda, Matrix &v) const;
        void eigen(Matrix &lambda, Matrix &v) const;
		
		Matrix func(Func0 f) const;
		Matrix func(Func1 f) const;
		Matrix func(Func2 f) const;
		Matrix func(Func3 f) const;
	
	private:
	
		typedef double *pdouble;
		
		static constexpr double EPS = 1E-10;
	
		Usecnt uc;
		Block<pdouble> *index;
		Block<double> *num;
		
		int gauss_swap;
		
		void setindex();
		void makeonly();
		
		static const int FAST_MULTIPLE_SIZE = 20;
		
        int jacobi_maxind(Matrix &S, int k) const;
        int jacobi_update(Block<bool> &changed, Matrix &e, int k, double t) const;
        void jacobi_rotate(Matrix &S, int k, int l, int i, int j, double c, double s) const;
};

#include "matrix.cpp"
