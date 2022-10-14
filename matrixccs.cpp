#include "matrixccs.h"

MatrixCCS::MatrixCCS()
{
    size = 0;
    lj = 0;
    A = nullptr;
    LI = nullptr;
    LJ = nullptr;
}
/* Проходит одну диагональ (столбец в новом формате) */
void MatrixCCS::filling(MatrixTL &mtrx, unsigned short int st_n, unsigned short int end_n,
                        unsigned short int st_m, unsigned short int end_m)
{
    unsigned short int i = st_n;
    unsigned short int j = st_m;
    bool flag = true;
    while (i <= end_n and j >= end_m){
        int val = mtrx.getValue(i, j);
        if (val != 0){
            A[size] = val;
            LI[size] = i + 1;
            if (flag){
                lj = size + 1;
                flag = false;
            }
            if (size != 0){
                LJ[size-1] = lj;
            }
            size++;
        }
        i++;
        j--;
    }
}

MatrixCCS::MatrixCCS(MatrixTL &mtrx)
{
    unsigned short int n = mtrx.getN();                   // Работа с индексами
    unsigned short int p = mtrx.getP();
    unsigned short int q = mtrx.getQ();
    unsigned short int m = mtrx.getM();
    unsigned short int st_n = 0;
    unsigned short int end_n = p;
    unsigned short int st_m = p;
    unsigned short int end_m = 0;
    unsigned short int min;
    if (n >= m)
        min = m;
    else
        min = n;
    size = 0;
    A = new int[n*m];
    LI = new int[n*m];
    LJ = new int[n*m];
    lj = 0;
    for (unsigned short int i = 0; i < min - p - 1; i++){ // До диагонали
        filling(mtrx, st_n, end_n, st_m, end_m);
        end_n++;
        st_m++;
    }
    if (min == m){
        for (unsigned short int i = 0; i < n - q; i++){   // После (матрица получилась широкая)
            filling(mtrx, st_n, end_n, st_m, end_m);
            if (end_n < n - 1)
                end_n++;
            else
                end_m++;
            st_n++;
        }
    }else{
        for (unsigned short int i = 0; i < m - q; i++){   // После (матрица получилась вытянутая)
            filling(mtrx, st_n, end_n, st_m, end_m);
            if (st_m < m - 1)
                st_m++;
            else
                st_n++;
            end_m++;
        }
    }
    LJ[size - 1] = size + 1;
}
ostream& operator << (ostream &out, MatrixCCS &matrix){
    unsigned int len = matrix.size;
    out << "A: ";
    for (unsigned int i = 0; i < len; i++){
        out << matrix.A[i] << " ";
    }
    out << endl << "LI: ";
    for (unsigned int i = 0; i < len; i++){
        out << matrix.LI[i] << " ";
    }
    out << endl << "LJ: ";
    for (unsigned int i = 0; i < len; i++){
        out << matrix.LJ[i] << " ";
    }
    return out;
}
