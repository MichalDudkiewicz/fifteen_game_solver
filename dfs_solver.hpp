#ifndef FIFTEEN_GAME_SOLVER_DFS_SOLVER_HPP
#define FIFTEEN_GAME_SOLVER_DFS_SOLVER_HPP

#include "blind_solver.hpp"

namespace fifteen
{
    class DFSSolver : public BlindSolver {
    public:
        DFSSolver(const std::vector<Operation>& operationOrder, unsigned int recursionDepthLimit);

    public:
        Solution solve(const std::shared_ptr<Node> &rootNode) override;

    private:
        unsigned int mRecursionDepthLimit;
    };
}

#endif //FIFTEEN_GAME_SOLVER_DFS_SOLVER_HPP
