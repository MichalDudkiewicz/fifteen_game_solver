#ifndef FIFTEEN_GAME_SOLVER_MANHATTAN_HEURISTIC_HPP
#define FIFTEEN_GAME_SOLVER_MANHATTAN_HEURISTIC_HPP

#include "heuristic.hpp"

namespace fifteen
{
    class ManhattanHeuristic : public Heuristic {
    private:
        unsigned int estimateMinPathCostToTarget(const std::shared_ptr<Node> &node) const override;

    public:
        static std::string name();
    };
}

#endif //FIFTEEN_GAME_SOLVER_MANHATTAN_HEURISTIC_HPP
