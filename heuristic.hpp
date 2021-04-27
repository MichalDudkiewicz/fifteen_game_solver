#ifndef FIFTEEN_GAME_SOLVER_HEURISTIC_HPP
#define FIFTEEN_GAME_SOLVER_HEURISTIC_HPP

#include "node.hpp"

namespace fifteen
{
    class Heuristic
    {
    public:
        virtual ~Heuristic() = default;

        bool operator()(const std::shared_ptr<Node>& firstNode, const std::shared_ptr<Node>& secondNode) const;

    private:
        virtual unsigned int estimateMinPathCostToTarget(const std::shared_ptr<Node> &node) const = 0;
        unsigned int estimatePathCostToTarget(const std::shared_ptr<Node> &node) const;
    };
}

#endif //FIFTEEN_GAME_SOLVER_HEURISTIC_HPP
