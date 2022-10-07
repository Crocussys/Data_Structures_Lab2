#include <iostream>
#include <fstream>
#include "matrixtl.h"
#include "matrixccs.h"

using namespace std;

int main()
{
    fstream file("matrix1.txt", ios::in);
    MatrixTL m1;
    file >> m1;
    file.close();
    file.open("matrix3.txt", ios::in);
    MatrixTL m2;
    file >> m2;
    file.close();
    MatrixTL m3 = m1 + m2;
    cout << m3 << endl;
    MatrixCCS m4;
    m4.fill(m3);
    cout << m4 << endl;
    return 0;
}
