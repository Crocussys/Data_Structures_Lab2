#ifndef MATRIXTL_H
#define MATRIXTL_H
#include <iostream>

using namespace std;


/* Матрица ленточного строчного формата */
class MatrixTL
{
private:
    unsigned short int N;
    unsigned short int M;
    unsigned short int P;
    unsigned short int Q;
    int **arr;
public:
    MatrixTL();
    MatrixTL(unsigned short int n, unsigned short int p, unsigned short int q, int **array);

    unsigned short int getN();
    unsigned short int getP();
    unsigned short int getQ();
    unsigned short int getM();
    int getValue(int i, int j);  // Получить значение элемента

    friend istream& operator >> (istream &in, MatrixTL &matrix);
    friend ostream& operator << (ostream &out, MatrixTL &matrix);
    friend MatrixTL operator + (MatrixTL &m1, MatrixTL &m2);
};

#endif // MATRIXTL_H
