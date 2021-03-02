#include "BRStep.h"
#include <iostream>
#include <iomanip>


void Step::Print()
{	
	int printNumberStep = stepNumber + 1;

	if (printNumberStep == 1) {
		std::cout << std::setw(4) << "k";
		std::cout << std::setw(2) << "x";
		std::cout << std::setw(2) << "y";
		std::cout << std::setw(6) << "A";
		std::cout << std::setw(6 * firstPlayerScores.size() - 6) << "";
		std::cout << std::setw(6) << "B";
		std::cout << std::setw(6 * secondPlayerScores.size() - 6) << "";
		std::cout << std::setw(2) << "|" << " ";
		std::cout << std::setw(7) << "Vup";
		std::cout << std::setw(7) << "Vlow";
		std::cout << std::setw(7) << "err";
		std::cout << std::endl;
	}

	std::cout << std::setw(4) << printNumberStep;
	std::cout << std::setw(2) << firstPlayerStrategy + 1;
	std::cout << std::setw(2) << secondPlayerStrategy + 1;
	for (const auto& iter : firstPlayerScores) {
		std::cout << std::fixed << std::setprecision(0) << std::setw(6) << iter;
	}
	for (const auto& iter : secondPlayerScores) {
		std::cout << std::fixed << std::setprecision(0) << std::setw(6) << iter;
	}
	std::cout << std::setw(2) << "|" << " ";
	std::cout << std::setw(7) << std::setprecision(3) << avgUpperBound;
	std::cout << std::setw(7) << std::setprecision(3) << avgLowerBound;
	std::cout << std::setw(7) << std::setprecision(3) << error;
	std::cout << std::endl;
}
