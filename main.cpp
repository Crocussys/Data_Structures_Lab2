#include <iostream>
#include <fstream>
#include "matrixtl.h"
#include "matrixccs.h"

using namespace std;

void usage(){
    cout << "Lab2 [path_1] [path_2]" << endl << endl;
    cout << "path_1 - Файл матрицы 1" << endl;
    cout << "path_2 - Файл матрицы 2" << endl;
    cout << endl << "Error: Not enough arguments" << endl;
}

bool checkFile(fstream &file){
    if (!file){
        cout << "File open error" << endl;
        return false;
    }else
        return true;
}

int main(int argc, char* argv[])
{
    if (argc < 2){
        usage();
        return -2;
    }
    fstream file(argv[1], ios::in);
    if (!checkFile(file))
        return -1;
    MatrixTL m1;
    file >> m1;                                 // Считывание матрицы 1 из файла
    file.close();
    cout << m1 << endl;                         // Вывод для проверки

    file.open(argv[2], ios::in);
    if (!checkFile(file))
        return -1;
    MatrixTL m2;
    file >> m2;                                 // Считывание матрицы 2 из файла
    file.close();
    cout << m2 << endl;                         // Вывод для проверки

    MatrixTL m3 = m1 + m2;                      // Сложение матриц
    cout << m3 << endl;                         // Вывод для проверки

    MatrixCCS m4(m3);                           // Преобразование в CCS
    cout << m4 << endl;                         // Вывод
    return 0;
}
