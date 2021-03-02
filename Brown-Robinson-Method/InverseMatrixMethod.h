#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <stdexcept>

using Matrix = std::vector<std::vector<double>>;

class InverseMatrixMethod {
private:
    Matrix m_matrix;
    Matrix m_firstPlayerStrategy;
    Matrix m_secondPlayerStrategy;
    double m_gameValue;

    double GetGameValue();
    Matrix GetFirstPlayerStrategy();
    Matrix GetSecondPlayerStrategy();

    Matrix GetInverse(const Matrix vect);
    Matrix GetCofactor(const Matrix vect);
    Matrix GetTranspose(const Matrix matrix1);
    Matrix MultMatrix(const Matrix lhs, const Matrix rhs);
    double GetDeterminant(const Matrix vect);

    void   PrintMatrix(Matrix m);

public:
    InverseMatrixMethod() {}
    InverseMatrixMethod(Matrix matrix);
    void iSolve();
    void iPrintResult();

};