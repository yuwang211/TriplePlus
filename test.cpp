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
    s.eigen(lambda, v);
    for (int i = 0; i < lambda.col; ++i)
        printf("%.2lf ", lambda[0][i]);
    printf("\n");
    for (int i = 0; i < v.row; ++i)
    {
        for (int j = 0; j < v.col; ++j)
            printf("%.2lf ", v[i][j]);
        printf("\n");
    }
    printf("\n");
}
