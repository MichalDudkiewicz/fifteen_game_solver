#include "manhattan_heuristic.hpp"

namespace fifteen
{
    unsigned int calculateMetricPartial(int rowIndex, int columnIndex, int value, int rowsNumber, int columnsNumber)
    {
        const int x2 = rowIndex;
        const int y2 = columnIndex;
        const int y1 = (value - 1) % columnsNumber;
        const int x1 = (value - 1) / rowsNumber;
        return std::abs(x2 - x1) + std::abs(y2 - y1);
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

    std::string ManhattanHeuristic::name() {
        return "manh";
    }
}