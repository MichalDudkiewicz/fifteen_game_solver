#ifndef FIFTEEN_GAME_SOLVER_BLIND_SOLVER_HPP
#define FIFTEEN_GAME_SOLVER_BLIND_SOLVER_HPP


#include <vector>
#include "operation.hpp"
#include "solver.hpp"

namespace fifteen
{
    class BlindSolver : public Solver {
    protected:
        explicit BlindSolver(std::vector<Operation> operationOrder);

        bool isOpened(const std::shared_ptr<Node> &node) const;

    protected:
        std::deque<std::shared_ptr<Node>> mOpenList;
        std::vector<Operation> mOperationOrder;
    };
}

#endif //FIFTEEN_GAME_SOLVER_BLIND_SOLVER_HPP
