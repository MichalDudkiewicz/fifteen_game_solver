#include "hamming_heuristic.hpp"

namespace fifteen
{
    unsigned int HammingHeuristic::estimateMinPathCostToTarget(const std::shared_ptr<Node> &node) const {
        const auto& gameBoard = node->state()->fifteenTable();
        unsigned int elementsNotInPlace = 0;
        u_int8_t targetElement = 1;
        for (const auto& row : gameBoard)
        {
            for (const auto& element : row)
            {
                if (element != 0)
                {
                    if (targetElement != element)
                    {
                        elementsNotInPlace++;
                    }
                }
                targetElement++;
            }
        }
        return elementsNotInPlace;
    }
}