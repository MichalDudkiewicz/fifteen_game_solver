#include "solver.hpp"

namespace fifteen
{
    bool Solver::isSolution(const std::shared_ptr<State> &state) const {
        const auto& gameBoard = state->fifteenTable();
        uint8_t valueToCheck = 0;
        for(const auto& row : gameBoard)
        {
            for(const auto& value : row)
            {
                if (value != valueToCheck)
                {
                    return false;
                }
                valueToCheck++;
            }
        }
        return true;
    }

    bool Solver::isClosed(const Node &node) const {
        return mClosedList.count(node);
    }
}
