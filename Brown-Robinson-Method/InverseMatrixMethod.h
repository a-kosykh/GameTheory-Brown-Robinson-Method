#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <stdexcept>

using Matrix = std::vector<std::vector<double>>;

class InverseMatrixMethod {
private:
    Matrix m_matrix;                // исходная матрица
    Matrix m_firstPlayerStrategy;   // смешанные стратегии 1ого игрока
    Matrix m_secondPlayerStrategy;  // смешанные стратегии 2ого игрока
    double m_gameValue;             // цена игры

    double GetGameValue();              // вычисление цены игры
    Matrix GetFirstPlayerStrategy();    // вычисление смешанных стратегий 1ого игрока
    Matrix GetSecondPlayerStrategy();   // вычисление смешанных стратегий 2ого игрока

    Matrix GetInverse(const Matrix vect);                    // вычисление обратной матрицы
    Matrix GetCofactor(const Matrix vect);                   // вычисление алгебраического дополнения
    Matrix GetTranspose(const Matrix matrix1);               // транспонирование матрицы
    Matrix MultMatrix(const Matrix lhs, const Matrix rhs);   // перемножение матриц
    double GetDeterminant(const Matrix vect);                // вычисление определителя матрицы

    void   PrintMatrix(Matrix m); // вывод матрицы

public:
    InverseMatrixMethod() {}
    InverseMatrixMethod(Matrix matrix);
    void iSolve();       // решение матричным методом
    void iPrintResult(); // вывод решения

};