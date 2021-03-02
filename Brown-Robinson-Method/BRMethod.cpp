#include "BRMethod.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <limits.h>
#include "pbPlots.hpp"
#include "supportLib.hpp"


BrownRobinsonAlgorithm::BrownRobinsonAlgorithm(Matrix matrix, int maxSteps, double error)
{
	m_matrix = matrix;
	m_maxSteps = maxSteps;
	m_error = error;
	m_firstPlayerStrategy = 0;
	m_secondPlayerStrategy = 0;
	m_minAvgUpperBound = DBL_MAX;
	m_maxAvgLowerBound = 0;
	m_totalSteps = 0;

	for (size_t iter = 0; iter < m_matrix.size(); ++iter) {
		m_prevFirstPlayerScores.push_back(0);
	}

	for (size_t iter = 0; iter < m_matrix[m_secondPlayerStrategy].size(); ++iter) {
		m_prevSecondPlayerScores.push_back(0);
	}
}

int BrownRobinsonAlgorithm::GetFirstPlayerStrategy()
{
	std::vector<int> indexesOfMaxElements;
	int maxElement = *std::max_element(m_prevFirstPlayerScores.begin(), m_prevFirstPlayerScores.end());
	for (auto iter = m_prevFirstPlayerScores.begin(); iter != m_prevFirstPlayerScores.end(); iter++) {
		if (*iter >= maxElement) {
			indexesOfMaxElements.push_back(std::distance(m_prevFirstPlayerScores.begin(), iter));
			maxElement = *iter;
		}
	}
	return indexesOfMaxElements[0];


	std::vector<int> indexes;
	std::vector<double> maxValues;
	for (const auto& iter : indexesOfMaxElements) {
		std::vector<double> tempSecondPlayerScores;
		for (size_t iter2 = 0; iter2 < m_prevSecondPlayerScores.size(); iter2++) {
			tempSecondPlayerScores.push_back(m_prevSecondPlayerScores[iter2] + m_matrix[iter][iter2]);
		}
		indexes.push_back(iter);
		maxValues.push_back(*std::max_element(tempSecondPlayerScores.begin(), tempSecondPlayerScores.end()));
	}
	return indexes[std::distance(maxValues.begin(),
		std::max_element(maxValues.begin(),
			maxValues.end()))];
}

int BrownRobinsonAlgorithm::GetSecondPlayerStrategy()
{
	std::vector<int> indexesOfMinElements;
	int minElement = *std::min_element(m_prevSecondPlayerScores.begin(), m_prevSecondPlayerScores.end());
	for (auto iter = m_prevSecondPlayerScores.begin(); iter != m_prevSecondPlayerScores.end(); iter++) {
		if (*iter <= minElement) {
			indexesOfMinElements.push_back(std::distance(m_prevSecondPlayerScores.begin(), iter));
			minElement = *iter;
		}
	}
	return indexesOfMinElements[0];

	std::vector<int> indexes;
	std::vector<double> maxValues;
	for (const auto& iter : indexesOfMinElements) {
		std::vector<double> tempFirstPlayerScores;
		for (size_t iter2 = 0; iter2 < m_prevFirstPlayerScores.size(); iter2++) {
			tempFirstPlayerScores.push_back(m_prevFirstPlayerScores[iter2] + m_matrix[iter2][iter]);
		}
		indexes.push_back(iter);
		maxValues.push_back(*std::max_element(tempFirstPlayerScores.begin(), tempFirstPlayerScores.end()));
	}
	return indexes[std::distance(maxValues.begin(),
		std::min_element(maxValues.begin(),
			maxValues.end()))];
}

void BrownRobinsonAlgorithm::GetAnswer()
{
	size_t numberOfStrategies = m_matrix.size();
	
	std::map<int, size_t> firstPlayerStrategyCounts;
	for (size_t i = 0; i < numberOfStrategies; ++i) {
		firstPlayerStrategyCounts.insert(std::pair<int, size_t>(i, 0));
	}
	for (const auto& step : m_steps) {
		++firstPlayerStrategyCounts[step.firstPlayerStrategy];
	}
	for (const auto& strategy : firstPlayerStrategyCounts) {
		m_firstPlayerAnswer.push_back(static_cast<double>(strategy.second) / (static_cast<double>(m_totalSteps) + 1));
	}

	std::map<int, size_t> secondPlayerStrategyCounts;
	for (size_t i = 0; i < numberOfStrategies; ++i) {
		secondPlayerStrategyCounts.insert(std::pair<int, size_t>(i, 0));
	}
	for (const auto& step : m_steps) {
		++secondPlayerStrategyCounts[step.secondPlayerStrategy];
	}
	for (const auto& strategy : secondPlayerStrategyCounts) {
		m_secondPlayerAnswer.push_back(static_cast<double>(strategy.second) / (static_cast<double>(m_totalSteps) + 1));
	}
}

void BrownRobinsonAlgorithm::Solve()
{
	for (unsigned int stepIter = 0; stepIter < m_maxSteps; ++stepIter) {
		Step currentStep(stepIter);

		currentStep.firstPlayerStrategy = m_firstPlayerStrategy;
		currentStep.secondPlayerStrategy = m_secondPlayerStrategy;

		for (size_t iter = 0; iter < m_matrix.size(); ++iter) {
			currentStep.firstPlayerScores.push_back(m_matrix[iter][currentStep.secondPlayerStrategy] + m_prevFirstPlayerScores[iter]);
		}

		for (size_t iter = 0; iter < m_matrix[currentStep.secondPlayerStrategy].size(); ++iter) {
			currentStep.secondPlayerScores.push_back(m_matrix[currentStep.firstPlayerStrategy][iter] + m_prevSecondPlayerScores[iter]);
		}

		currentStep.avgUpperBound = *std::max_element(currentStep.firstPlayerScores.begin(), currentStep.firstPlayerScores.end()) / static_cast<double>(stepIter+1);
		currentStep.avgLowerBound = *std::min_element(currentStep.secondPlayerScores.begin(), currentStep.secondPlayerScores.end()) / static_cast<double>(stepIter+1);
		if (currentStep.avgUpperBound <= m_minAvgUpperBound) {
			m_minAvgUpperBound = currentStep.avgUpperBound;
		}
		if (currentStep.avgLowerBound >= m_maxAvgLowerBound) {
			m_maxAvgLowerBound = currentStep.avgLowerBound;
		}

		currentStep.error = m_minAvgUpperBound - m_maxAvgLowerBound;

		m_steps.push_back(currentStep);

		if (currentStep.error < m_error) {
			m_totalSteps = currentStep.stepNumber;
			m_finalError = currentStep.error;
			break;
		}
		else {
			m_prevFirstPlayerScores = currentStep.firstPlayerScores;
			m_prevSecondPlayerScores = currentStep.secondPlayerScores;

			m_firstPlayerStrategy = GetFirstPlayerStrategy();
			m_secondPlayerStrategy = GetSecondPlayerStrategy();
		}
	}
	GetAnswer();
}

void BrownRobinsonAlgorithm::SaveErrorPlot()
{
	if (m_steps.size() == 0) return;
	
	RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();

	ScatterPlotSeries* errorSeries = GetDefaultScatterPlotSeriesSettings();
	std::vector<double> xs;
	std::vector<double> ys;
	for (const Step& step : m_steps) {
		xs.push_back(step.stepNumber);
		ys.push_back(step.error);
	}
	errorSeries->xs = &xs;
	errorSeries->ys = &ys; 
	errorSeries->linearInterpolation = true;

	ScatterPlotSettings* setting = GetDefaultScatterPlotSettings();
	setting->width = 600;
	setting->height = 400;
	setting->autoBoundaries = true;
	setting->autoPadding = true;
	setting->title = toVector(L"Error plot");
	setting->xLabel = toVector(L"Steps");
	setting->yLabel = toVector(L"Error");

	setting->scatterPlotSeries->push_back(errorSeries);

	DrawScatterPlotFromSettings(imageReference, setting);

	std::vector<double>* pngdata = ConvertToPNG(imageReference->image);
	WriteToFile(pngdata, "errorPlot.png");
	DeleteImage(imageReference->image);
}

void BrownRobinsonAlgorithm::SaveGameValuePlot()
{
	if (m_steps.size() == 0) return;

	RGBABitmapImageReference* imageReference = CreateRGBABitmapImageReference();
	ScatterPlotSeries* lowerGameValueSeries = GetDefaultScatterPlotSeriesSettings();
	ScatterPlotSeries* upperGameValueSeries = GetDefaultScatterPlotSeriesSettings();
	std::vector<double> xLower, yLower, xUpper, yUpper;
	for (const Step& step : m_steps) {
		xLower.push_back(step.stepNumber);
		yLower.push_back(step.avgLowerBound);
		xUpper.push_back(step.stepNumber);
		yUpper.push_back(step.avgUpperBound);
	}
	lowerGameValueSeries->xs = &xLower;
	lowerGameValueSeries->ys = &yLower;
	upperGameValueSeries->xs = &xUpper;
	upperGameValueSeries->ys = &yUpper;

	ScatterPlotSettings* setting = GetDefaultScatterPlotSettings();
	setting->width = 600;
	setting->height = 400;
	setting->autoBoundaries = true;
	setting->autoPadding = true;
	setting->title = toVector(L"Game value plot");
	setting->xLabel = toVector(L"Steps");
	setting->yLabel = toVector(L"Game value");

	setting->scatterPlotSeries->push_back(lowerGameValueSeries);
	setting->scatterPlotSeries->push_back(upperGameValueSeries);

	DrawScatterPlotFromSettings(imageReference, setting);

	std::vector<double>* pngdata = ConvertToPNG(imageReference->image);
	WriteToFile(pngdata, "gameValuePlot.png");
	DeleteImage(imageReference->image);
}

void BrownRobinsonAlgorithm::iSolve()
{
	Solve();
}

void BrownRobinsonAlgorithm::iPrintAnswer()
{
	std::cout << "*****Brown-Robinson method*****" << std::endl;
	for (auto& step : m_steps) {
		step.Print();
	}
	std::cout << "x*: {";
	for (const auto firstPlayerStrategy : m_firstPlayerAnswer) {
		std::cout << firstPlayerStrategy << " ";
	}
	std::cout << "}" << std::endl;

	std::cout << "y*: {";
	for (const auto secondPlayerStrategy : m_secondPlayerAnswer) {
		std::cout << secondPlayerStrategy << " ";
	}
	std::cout << "}" << std::endl;
	std::cout << "error: " << m_finalError;
	std::cout << std::endl;
}

void BrownRobinsonAlgorithm::iSavePlots()
{
	SaveErrorPlot();
	SaveGameValuePlot();
}
