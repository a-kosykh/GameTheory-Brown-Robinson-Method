#pragma once
#include <vector>


//  ласс "Ўаг алгоритма Ѕрауна-–обинсон"
class Step {
private:

public:
	Step(int stepNumber): stepNumber(stepNumber) {}
	~Step() {}

	int					stepNumber;				// номер шага
	int					firstPlayerStrategy;	// стратеги€ 1ого игрока
	int					secondPlayerStrategy;	// стратеги€ 2ого игрока
	std::vector<double>	firstPlayerScores;		// вектор значений 1ого игрока
	std::vector<double>	secondPlayerScores;		// вектор значений 2ого игрока
	double				avgUpperBound;			// верхн€€ граница цены игры
	double				avgLowerBound;			// нижн€€ граница цены игры
	double				error;					// погрешнность

	void Print(); // вывод шага на экран
};