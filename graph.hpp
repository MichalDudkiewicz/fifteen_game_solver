#ifndef FIFTEEN_GAME_SOLVER_GRAPH_HPP
#define FIFTEEN_GAME_SOLVER_GRAPH_HPP

#include <utility>

#include "node.hpp"
#include "solver.hpp"

namespace fifteen
{
    class Graph {
    public:
        Graph(const std::shared_ptr<Node> initialNode, std::shared_ptr<Solver> solver)
        : mInitialNode(initialNode), mSolver(std::move(solver))
        {
        }

        Solution solution() const;

    private:
        std::shared_ptr<Node> mInitialNode;
        std::shared_ptr<Solver> mSolver;
    };
}

#endif //FIFTEEN_GAME_SOLVER_GRAPH_HPP
