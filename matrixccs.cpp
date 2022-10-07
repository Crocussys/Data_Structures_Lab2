#include "matrixccs.h"

MatrixCCS::MatrixCCS()
{
    size = 0;
    lj = 0;
    A = nullptr;
    LI = nullptr;
    LJ = nullptr;
}
void MatrixCCS::filling(MatrixTL &mtrx, unsigned short int st_n, unsigned short int end_n,
                        unsigned short int st_m, unsigned short int end_m)
{
    int i = st_n;
    int j = st_m;
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

void MatrixCCS::fill(MatrixTL &mtrx)
{
    unsigned short int st_n = 0;
    unsigned short int end_n = 0;
    unsigned short int st_m = 0;
    unsigned short int end_m = 0;
    unsigned short int n = mtrx.getN();
    unsigned short int m = mtrx.getM();
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
    for (int i = 0; i < min; i++){
        filling(mtrx, st_n, end_n, st_m, end_m);
        end_n++;
        st_m++;
    }
    end_n--;
    st_m--;
    if (min == m){
        if (end_n < n - 1) end_n++;
        st_n++;
        for (int i = 0; i < n - 1; i++){
            filling(mtrx, st_n, end_n, st_m, end_m);
            if (end_n < n - 1) end_n++;
            st_n++;
        }
    }else{      // Этот кусок кода работает неправильно
        if (end_m < m - 1) end_m++;
        st_m++;
        for (int i = 0; i < n - 1; i++){
            filling(mtrx, st_n, end_n, st_m, end_m);
            if (end_m < m - 1) end_m++;
            st_m++;
        }      //--------------------------------------
    }
    LJ[size - 1] = size + 1;
}
ostream& operator << (ostream &out, MatrixCCS &matrix){
    int len = matrix.size;
    out << "A: ";
    for (int i = 0; i < len; i++){
        out << matrix.A[i] << " ";
    }
    out << endl << "LI: ";
    for (int i = 0; i < len; i++){
        out << matrix.LI[i] << " ";
    }
    out << endl << "LJ: ";
    for (int i = 0; i < len; i++){
        out << matrix.LJ[i] << " ";
    }
    return out;
}
