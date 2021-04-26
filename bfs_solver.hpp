#ifndef FIFTEEN_GAME_SOLVER_BFS_SOLVER_HPP
#define FIFTEEN_GAME_SOLVER_BFS_SOLVER_HPP

#include "solver.hpp"
#include "node.hpp"
#include <vector>
#include "blind_solver.hpp"
#include <unordered_set>

namespace fifteen
{
    class BFSSolver : public BlindSolver {
    public:
        explicit BFSSolver(const std::vector<Operation>& operationOrder);

    public:
        Solution solve(const std::shared_ptr<Node> &rootNode) override;
    };
}

#endif //FIFTEEN_GAME_SOLVER_BFS_SOLVER_HPP
