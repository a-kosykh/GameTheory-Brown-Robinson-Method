#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "BRMethod.h"
#include "InverseMatrixMethod.h"

using Matrix = std::vector<std::vector<double>>;

// Функция чтения матрицы из файла
Matrix ReadFromFile(std::string filename) {
	Matrix mat;
	std::ifstream ifs(filename);
	if (!ifs.is_open()) {
		throw std::runtime_error("Can't open file!");
	}

	std::string tempStr;
	double tempDouble;

	while (std::getline(ifs, tempStr)) {
		std::istringstream iss(tempStr);
		std::vector<double> tempRow;
		while (iss >> tempDouble) {
			tempRow.push_back(tempDouble);

		}
		mat.push_back(tempRow);
	}
	return mat;
}

int main(int argc, char* argv[]) {
	Matrix matrix;
	try {
		matrix = ReadFromFile(argv[1]);
		if (matrix.size() != matrix[0].size()) {
			throw std::runtime_error("Matrix is not quadratic!");
		}
	}
	catch (std::runtime_error& e) { std::cerr << e.what() << std::endl; return 1; }
	
	// Решение методом обратной матрицы
	InverseMatrixMethod imm(matrix);
	imm.iSolve();
	imm.iPrintResult();

	std::cout << std::endl << std::endl;
	double error = atof(argv[2]);
	// Решение методом Брауна-Робинсона
	BrownRobinsonAlgorithm br1(matrix, error);
	br1.iSolve();
	br1.iPrintAnswer();
	br1.iSavePlots();

	return 0;
}