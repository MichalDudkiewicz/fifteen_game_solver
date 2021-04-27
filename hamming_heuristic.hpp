#ifndef FIFTEEN_GAME_SOLVER_HAMMING_HEURISTIC_HPP
#define FIFTEEN_GAME_SOLVER_HAMMING_HEURISTIC_HPP

#include "heuristic.hpp"
#include "node.hpp"

namespace fifteen
{
    class HammingHeuristic : public Heuristic
    {
    public:
        unsigned int estimateMinPathCostToTarget(const std::shared_ptr<Node> &node) const override;
    };
}

#endif //FIFTEEN_GAME_SOLVER_HAMMING_HEURISTIC_HPP
