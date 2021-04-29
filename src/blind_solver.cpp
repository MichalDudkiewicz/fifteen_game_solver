#include "blind_solver.hpp"

#include <utility>

namespace fifteen
{
    BlindSolver::BlindSolver(std::vector<Operation> operationOrder)
    : mOperationOrder(std::move(operationOrder))
    {
    }

    bool BlindSolver::isOpened(const std::shared_ptr<Node> &node) const {
        const auto it = std::find_if(mOpenList.begin(), mOpenList.end(), [&](const auto& openedNode){
            return *(openedNode->state()) == *(node->state());
        });
        return it != mOpenList.end();
    }
}