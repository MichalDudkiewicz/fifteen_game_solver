#ifndef FIFTEEN_GAME_SOLVER_SOLVER_HPP
#define FIFTEEN_GAME_SOLVER_SOLVER_HPP

#include "node.hpp"
#include <memory>
#include "solution.hpp"
#include <unordered_set>

namespace fifteen
{
    class Solver
    {
    public:
        virtual ~Solver() = default;

        virtual Solution solve(const std::shared_ptr<Node>& initialNode) = 0;

    protected:
        bool isSolution(const std::shared_ptr<State> &state) const;

        bool isOpened(const std::shared_ptr<Node> &node) const;

        bool isClosed(const Node &node) const;

    protected:
        std::deque<std::shared_ptr<Node>> mOpenList;
        std::unordered_set<Node, NodeHash> mClosedList;
    };
}

#endif //FIFTEEN_GAME_SOLVER_SOLVER_HPP
