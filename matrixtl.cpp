#include "matrixtl.h"

MatrixTL::MatrixTL()
{
    N = 0;
    M = 0;
    P = 0;
    Q = 0;
    arr = nullptr;
}
MatrixTL::MatrixTL(unsigned short int n, unsigned short int p, unsigned short int q, int **array)
{
    N = n;
    P = p;
    Q = q;
    M = p + q + 1;
    arr = array;
}
unsigned short int MatrixTL::getN()
{
    return N;
}
unsigned short int MatrixTL::getP()
{
    return P;
}
unsigned short int MatrixTL::getQ()
{
    return Q;
}
unsigned short int MatrixTL::getM()
{
    return M;
}
int MatrixTL::getValue(unsigned short int i, unsigned short int j)
{
    if (i >= N or j >= M)
        throw "List index out of range";
    return arr[i][j];
}
istream& operator >> (istream &in, MatrixTL &matrix)
{
    unsigned short int n;
    unsigned short int p = 0;
    unsigned short int q = 0;
    in >> n;                                          // Считываем размер матрицы
    int** input_arr = new int* [n];
    for (unsigned short int i = 0; i < n; i++){
        input_arr[i] = new int [n];
        for (unsigned short int j = 0; j < n; j++){
            in >> input_arr[i][j];                    // Считываем саму матрицу
        }
    }
    for (unsigned short int k = 1; k < n; k++){       // Поиск нулевой диагонали
        unsigned short int i = k;                     // Снизу (слева) от главной диагонали
        unsigned short int j = 0;
        bool flag = true;
        for (unsigned short int l = 1; l < n - k + 1; l++){
            if (input_arr[i][j] != 0){
                p++;                                  // Для вычисления p
                flag = false;
                break;
            }
            i++;
            j++;
        }
        if (flag)
            break;
    }
    for (unsigned short int k = 1; k < n; k++){       // Поиск нулевой диагонали
        unsigned short int i = 0;                     // Сверху (справа) от главной диагонали
        unsigned short int j = k;
        bool flag = true;
        for (unsigned short int l = 1; l < n - k + 1; l++){
            if (input_arr[i][j] != 0){
                q++;                                  // Для вычисления q
                flag = false;
                break;
            }
            i++;
            j++;
        }
        if (flag)
            break;
    }
    int** ans_arr = new int* [n];
    for (unsigned short int i = 0; i < n; i++){
        ans_arr[i] = new int [p+q+1];
        for (unsigned short int j = 0; j < p+q+1; j++){
            if (j - p + i >= 0 and j - p + i < n){
                ans_arr[i][j] = input_arr[i][j-p+i];     // Упаковываем матрицу
            }else{
                ans_arr[i][j] = 0;
            }
        }
    }
    delete [] input_arr;     // Удаляем исходную матрицу
    matrix.N = n;            // Создаём матрицу нашего формата
    matrix.P = p;
    matrix.Q = q;
    matrix.M = p + q + 1;
    matrix.arr = ans_arr;
    return in;
}
ostream& operator << (ostream &out, MatrixTL &matrix)
{
    for (unsigned short int i = 0; i < matrix.N; i++){        // Вывод в нашем формате
        for (unsigned short int j = 0; j < matrix.M; j++){
            out << matrix.arr[i][j] << ' ';
        }
        out << endl;
    }
    return out;
}
MatrixTL operator + (MatrixTL &m1, MatrixTL &m2)
{
    if (m1.N != m2.N){
        throw "Размеры матрицы не совпадают";
    }
    MatrixTL* max_p_mtrx;
    MatrixTL* min_p_mtrx;
    MatrixTL* max_q_mtrx;
    MatrixTL* min_q_mtrx;
    if (m1.P >= m2.P){
        max_p_mtrx = &m1;
        min_p_mtrx = &m2;
    }else{
        max_p_mtrx = &m2;
        min_p_mtrx = &m1;
    }
    if (m1.Q >= m2.Q){
        max_q_mtrx = &m1;
        min_q_mtrx = &m2;
    }else{
        max_q_mtrx = &m2;
        min_q_mtrx = &m1;
    }
    unsigned short int n = m1.N;
    unsigned short int p = max_p_mtrx->P;
    unsigned short int q = max_q_mtrx->Q;
    int **array = new int* [n];
    for (unsigned short int i = 0; i < n; i++){
        array[i] = new int [p+q+1];                        // Создаём новую матрицу нужного размера
    }
    for (unsigned short int i = 0; i < n; i++){
        int k = max_p_mtrx->P - min_p_mtrx->P;
        for (unsigned short int j = 0; j < k; j++){
            array[i][j] = max_p_mtrx->arr[i][j];                           // Заполняем разницу p
        }
        for (unsigned short int j = k; j < min_p_mtrx->P + min_q_mtrx->Q + 1 + k; j++){
            array[i][j] = max_p_mtrx->arr[i][j] + min_p_mtrx->arr[i][j-k]; // Складываем общую часть
        }
        k += min_p_mtrx->P + min_q_mtrx->Q + 1;
        for (unsigned short int j = k; j < k + max_q_mtrx->Q - min_q_mtrx->Q; j++){
            if (max_q_mtrx == max_p_mtrx){                                 // Заполняем разницу q
                array[i][j] = max_q_mtrx->arr[i][j];
            }else{
                array[i][j] = max_q_mtrx->arr[i][j-max_p_mtrx->P+min_p_mtrx->P];
            }
        }
    }
    MatrixTL ans(n, p, q, array);  // Создаём полученную матрицу
    return ans;
}
