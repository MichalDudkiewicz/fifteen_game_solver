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

    bool Solver::isOpened(const std::shared_ptr<Node> &node) const {
        const auto it = std::find_if(mOpenList.begin(), mOpenList.end(), [&](const auto& openedNode){
            return *(openedNode->state()) == *(node->state());
        });
        return it != mOpenList.end();
    }

    bool Solver::isClosed(const Node &node) const {
        const auto it = std::find_if(mClosedList.begin(), mClosedList.end(), [&](const auto& closedNode){
            return *(closedNode.state()) == *(node.state());
        });
        return it != mClosedList.end();
    }
}
