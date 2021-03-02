#include "InverseMatrixMethod.h"

InverseMatrixMethod::InverseMatrixMethod(Matrix matrix)
{
	m_matrix = matrix;
}

void InverseMatrixMethod::iSolve()
{
    m_gameValue = GetGameValue();
    m_firstPlayerStrategy = GetFirstPlayerStrategy();
    m_secondPlayerStrategy = GetSecondPlayerStrategy();
}

void InverseMatrixMethod::iPrintResult()
{   
    std::cout << "*****Inverse matrix method*****" << std::endl;
    
    std::cout << "Initial matrix: " << std::endl;
    PrintMatrix(m_matrix);
    std::cout << std::endl;

    std::cout << "Inverse matrix: " << std::endl;
    PrintMatrix(GetInverse(m_matrix));
    std::cout << std::endl;

    std::cout << "x*: {";
    for (auto iter = m_firstPlayerStrategy[0].begin(); iter != m_firstPlayerStrategy[0].end(); ++iter)
        std::cout << std::setprecision(4) << *iter << " ";
    std::cout << "}" << std::endl;

    std::cout << "y*: {";
    for (auto iter = m_secondPlayerStrategy[0].begin(); iter != m_secondPlayerStrategy[0].end(); ++iter)
        std::cout << std::setprecision(4) << *iter << " ";
    std::cout << "}" << std::endl;

    std::cout << "Game value v:" << m_gameValue;
}

double InverseMatrixMethod::GetGameValue()
{
    Matrix ident = { {1, 1, 1} };
    Matrix identTrans = GetTranspose(ident);

    Matrix ansMatrix = MultMatrix(MultMatrix(ident, GetInverse(m_matrix)), identTrans);

    return (1 / ansMatrix[0][0]);
}

Matrix InverseMatrixMethod::GetFirstPlayerStrategy()
{
    Matrix ident = { {1, 1, 1} };
    Matrix ansMatrix = MultMatrix(ident, GetInverse(m_matrix));
    Matrix gameValueMatrix = { {m_gameValue} };
    return MultMatrix(gameValueMatrix, ansMatrix);
}

Matrix InverseMatrixMethod::GetSecondPlayerStrategy()
{
    Matrix ident = { {1, 1, 1} };
    Matrix ansMatrix = MultMatrix(GetInverse(m_matrix), GetTranspose(ident));
    Matrix gameValueMatrix = { {m_gameValue} };
    return MultMatrix(gameValueMatrix, GetTranspose(ansMatrix));
}

Matrix InverseMatrixMethod::GetInverse(const Matrix vect)
{
    if (GetDeterminant(vect) == 0) {
        throw std::runtime_error("Determinant is 0");
    }

    double d = 1.0 / GetDeterminant(vect);
    Matrix solution(vect.size(), std::vector<double>(vect.size()));

    for (size_t i = 0; i < vect.size(); i++) {
        for (size_t j = 0; j < vect.size(); j++) {
            solution[i][j] = vect[i][j];
        }
    }

    solution = GetTranspose(GetCofactor(solution));

    for (size_t i = 0; i < vect.size(); i++) {
        for (size_t j = 0; j < vect.size(); j++) {
            solution[i][j] *= d;
        }
    }

    return solution;
}

Matrix InverseMatrixMethod::GetCofactor(const Matrix vect)
{
    if (vect.size() != vect[0].size()) {
        throw std::runtime_error("Matrix is not quadratic");
    }

    Matrix solution(vect.size(), std::vector<double>(vect.size()));
    Matrix subVect(vect.size() - 1, std::vector<double>(vect.size() - 1));

    for (std::size_t i = 0; i < vect.size(); i++) {
        for (std::size_t j = 0; j < vect[0].size(); j++) {

            int p = 0;
            for (size_t x = 0; x < vect.size(); x++) {
                if (x == i) {
                    continue;
                }
                int q = 0;

                for (size_t y = 0; y < vect.size(); y++) {
                    if (y == j) {
                        continue;
                    }

                    subVect[p][q] = vect[x][y];
                    q++;
                }
                p++;
            }
            solution[i][j] = pow(-1, i + j) * GetDeterminant(subVect);
        }
    }
    return solution;
}

Matrix InverseMatrixMethod::GetTranspose(const Matrix matrix1)
{
    Matrix solution(matrix1[0].size(), std::vector<double>(matrix1.size()));

    for (size_t i = 0; i < matrix1.size(); i++) {
        for (size_t j = 0; j < matrix1[0].size(); j++) {
            solution[j][i] = matrix1[i][j];
        }
    }
    return solution;
}

Matrix InverseMatrixMethod::MultMatrix(const Matrix lhs, const Matrix rhs)
{
    const int lhsRowsCount = lhs.size();     
    const int lhsColsCount = lhs[0].size();  
    const int rhsColsCount = rhs[0].size();  

    Matrix solution(lhsRowsCount, std::vector<double>(rhsColsCount, 0));
    for (auto j = 0; j < rhsColsCount; ++j)
    {
        for (auto k = 0; k < lhsColsCount; ++k)
        {
            for (auto i = 0; i < lhsRowsCount; ++i)
            {
                solution[i][j] += lhs[i][k] * rhs[k][j];
            }
        }
    }
    return solution;
}

double InverseMatrixMethod::GetDeterminant(const Matrix vect)
{
    if (vect.size() != vect[0].size()) {
        throw std::runtime_error("Matrix is not quadratic");
    }
    int dimension = vect.size();

    if (dimension == 0) {
        return 1;
    }

    if (dimension == 1) {
        return vect[0][0];
    }

    if (dimension == 2) {
        return vect[0][0] * vect[1][1] - vect[0][1] * vect[1][0];
    }

    double result = 0;
    int sign = 1;
    for (int i = 0; i < dimension; i++) {

        Matrix subVect(dimension - 1, std::vector<double>(dimension - 1));
        for (int m = 1; m < dimension; m++) {
            int z = 0;
            for (int n = 0; n < dimension; n++) {
                if (n != i) {
                    subVect[m - 1][z] = vect[m][n];
                    z++;
                }
            }
        }

        result = result + sign * vect[0][i] * GetDeterminant(subVect);
        sign = -sign;
    }

    return result;
}

void InverseMatrixMethod::PrintMatrix(Matrix m)
{
    for (const auto& row : m) {
        for (const auto& element : row) {
            std::cout << std::setprecision(4) << element << " ";
        }
        std::cout << std::endl;
    }
}
