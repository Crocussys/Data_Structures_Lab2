#ifndef MATRIXCCS_H
#define MATRIXCCS_H
#include "matrixtl.h"


class MatrixCCS
{
private:
    int size;
    int *A;
    int *LI;
    int *LJ;

    void filling(MatrixTL &mtrx, unsigned short int st_n, unsigned short int end_n,
                 unsigned short int st_m, unsigned short int end_m);
    int lj;
public:
    MatrixCCS();
    void fill(MatrixTL &mtrx);
    friend ostream& operator << (ostream &out, MatrixCCS &matrix);
};

#endif // MATRIXCCS_H