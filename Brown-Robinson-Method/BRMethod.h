#pragma once
#include "BRStep.h"

using Matrix = std::vector<std::vector<double>>;

class BrownRobinsonAlgorithm {

private:
	Matrix m_matrix; // исходная матрица

	
	std::vector<Step>	m_steps; // вектор шагов метода
	std::vector<double>	m_prevFirstPlayerScores; // текущие значения первого игрока
	std::vector<double>	m_prevSecondPlayerScores; // текущие значения второго игрока
	int					m_firstPlayerStrategy; // текущая стратегий первого игрока
	int					m_secondPlayerStrategy;  // текущая стратегий второго игрока
	double				m_error; // текущая погрешнность

	double				m_finalError; // конечная погрешность
	double				m_minAvgUpperBound; // минимальное среднее значение верхней оценки цены игры
	double				m_maxAvgLowerBound; // максимальное среднее значение нижней оценки цены игры
	int					m_totalSteps; // конечное количество шагов алгоритма

	std::vector<double> m_firstPlayerAnswer; // смешанные стратегии 1ого игрока
	std::vector<double> m_secondPlayerAnswer; // смешанные стратегии 2ого игрока

	int		GetFirstPlayerStrategy(); // вычисление следующей стратегии 1ого игрока
	int		GetSecondPlayerStrategy(); // вычисление следующей стратегии 2ого игрока

	void	Solve(); // запуск алгоритма
	void	GetAnswer(); // получение ответа
	void	SaveErrorPlot(); // сохранение графика ошибки
	void	SaveGameValuePlot(); // сохранение графика цены игры
	bool	SaveTableToFile(); // сохранение таблицы метода

	
public:
	BrownRobinsonAlgorithm(Matrix matrix, double error);
	~BrownRobinsonAlgorithm() {}

	void iSolve(); // запуск алгоритма
	void iPrintAnswer(); // вывод результата в консоль
	void iSavePlots(); // сохранение графиков в файл
};