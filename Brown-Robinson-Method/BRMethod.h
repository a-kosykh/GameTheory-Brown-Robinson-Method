#pragma once
#include "BRStep.h"

using Matrix = std::vector<std::vector<double>>;

class BrownRobinsonAlgorithm {

private:
	Matrix m_matrix;

	double				m_error;
	std::vector<Step>	m_steps;
	std::vector<double>	m_prevFirstPlayerScores;
	std::vector<double>	m_prevSecondPlayerScores;
	int					m_firstPlayerStrategy;
	int					m_secondPlayerStrategy;

	int					m_maxSteps;
	double				m_finalError;
	double				m_minAvgUpperBound;
	double				m_maxAvgLowerBound;
	int					m_totalSteps;

	int		GetFirstPlayerStrategy();
	int		GetSecondPlayerStrategy();
	void	Solve();
	void	GetAnswer();
	void	SaveErrorPlot();
	void	SaveGameValuePlot();

	std::vector<double> m_firstPlayerAnswer;
	std::vector<double> m_secondPlayerAnswer;
public:
	BrownRobinsonAlgorithm(Matrix matrix, int maxSteps, double error);
	~BrownRobinsonAlgorithm() {}

	void iSolve();
	void iPrintAnswer();
	void iSavePlots();
};