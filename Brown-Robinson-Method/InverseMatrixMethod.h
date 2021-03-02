#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <stdexcept>

using Matrix = std::vector<std::vector<double>>;

class InverseMatrixMethod {
private:
    Matrix m_matrix;                // �������� �������
    Matrix m_firstPlayerStrategy;   // ��������� ��������� 1��� ������
    Matrix m_secondPlayerStrategy;  // ��������� ��������� 2��� ������
    double m_gameValue;             // ���� ����

    double GetGameValue();              // ���������� ���� ����
    Matrix GetFirstPlayerStrategy();    // ���������� ��������� ��������� 1��� ������
    Matrix GetSecondPlayerStrategy();   // ���������� ��������� ��������� 2��� ������

    Matrix GetInverse(const Matrix vect);                    // ���������� �������� �������
    Matrix GetCofactor(const Matrix vect);                   // ���������� ��������������� ����������
    Matrix GetTranspose(const Matrix matrix1);               // ���������������� �������
    Matrix MultMatrix(const Matrix lhs, const Matrix rhs);   // ������������ ������
    double GetDeterminant(const Matrix vect);                // ���������� ������������ �������

    void   PrintMatrix(Matrix m); // ����� �������

public:
    InverseMatrixMethod() {}
    InverseMatrixMethod(Matrix matrix);
    void iSolve();       // ������� ��������� �������
    void iPrintResult(); // ����� �������

};