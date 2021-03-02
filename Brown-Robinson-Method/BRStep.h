#pragma once
#include <vector>

class Step {
private:

public:
	Step(int stepNumber): stepNumber(stepNumber) {}
	~Step() {}

	int					stepNumber;
	int					firstPlayerStrategy;
	int					secondPlayerStrategy;
	std::vector<double>	firstPlayerScores;
	std::vector<double>	secondPlayerScores;
	double				avgUpperBound;
	double				avgLowerBound;
	double				error;

	void Print();
};