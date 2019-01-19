#define TPIMPORT_STRING
#define TPIMPORT_SIGNAL
#define TPIMPORT_MATRIX

#define TPL_DEBUG
#include "tplib/tplib.h"


using namespace tplib;

int main()
{
    Matrix s = Matrix::Make(4, 4,
                            {4, -30, 60, -35,
                            -30, 300, -675, 420,
                             60, -675, 1620, -1050,
                                -35, 420, -1050, 700});
    
    double l;
    Matrix lambda, v;
    s.evd(lambda, v);
    for (int i = 0; i < lambda.col; ++i)
        printf("%.2lf ", lambda[0][i]);
    printf("\n");
    for (int i = 0; i < v.row; ++i)
    {
        for (int j = 0; j < v.col; ++j)
            printf("%.2lf ", v[i][j]);
        printf("\n");
    }
    printf("\n\n");
    Matrix x = v * Matrix::Diag(lambda) * v.transpose();
    for (int i = 0; i < x.row; ++i)
    {
        for (int j = 0; j < x.col; ++j)
            printf("%.2lf ", x[i][j]);
        printf("\n");
    }
    printf("\n\n");
    
    
    Matrix t = Matrix::Make(3, 2,
                            {
                                0, 1,
                                1, 1,
                                1, 0
                            });
    Matrix u, sigma;
    t.svd(u, sigma, v);
    for (int i = 0; i < u.row; ++i)
    {
        for (int j = 0; j < u.col; ++j)
            printf("%.2lf ", u[i][j]);
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < sigma.row; ++i)
    {
        for (int j = 0; j < sigma.col; ++j)
            printf("%.2lf ", sigma[i][j]);
        printf("\n");
    }
    printf("\n");
    for (int i = 0; i < v.row; ++i)
    {
        for (int j = 0; j < v.col; ++j)
            printf("%.2lf ", v[i][j]);
        printf("\n");
    }
    printf("\n\n");
    
    x = u * sigma * v.transpose();
    for (int i = 0; i < x.row; ++i)
    {
        for (int j = 0; j < x.col; ++j)
            printf("%.2lf ", x[i][j]);
        printf("\n");
    }
    printf("\n");
    
}
