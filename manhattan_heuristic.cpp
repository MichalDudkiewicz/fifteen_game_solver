#include "manhattan_heuristic.hpp"

namespace fifteen
{
    unsigned int calculateMetricPartial(int rowIndex, int columnIndex, int value, int rowsNumber, int columnsNumber)
    {
        return std::abs(value % rowsNumber + value % columnsNumber - 1 - rowIndex - columnIndex);
    }

    unsigned int ManhattanHeuristic::estimateMinPathCostToTarget(const std::shared_ptr<Node> &node) const {
        const auto& gameBoard = node->state()->fifteenTable();
        unsigned int totalMetricValue = 0;
        const int rowsNumber = gameBoard.size();
        const int columnsNumber = gameBoard.front().size();
        for (int rowCounter = 0; rowCounter<rowsNumber; rowCounter++)
        {
            for (int columnCounter = 0; columnCounter<columnsNumber; columnCounter++)
            {
                const int elementValue = gameBoard[rowCounter][columnCounter];
                if (elementValue != 0)
                {
                    totalMetricValue += calculateMetricPartial(rowCounter, columnCounter, elementValue, rowsNumber, columnsNumber);
                }
            }
        }
        return totalMetricValue;
    }
}