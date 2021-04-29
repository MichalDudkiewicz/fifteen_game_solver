#ifndef FIFTEEN_GAME_SOLVER_HAMMING_HEURISTIC_HPP
#define FIFTEEN_GAME_SOLVER_HAMMING_HEURISTIC_HPP

#include "heuristic.hpp"
#include "node.hpp"

namespace fifteen
{
    class HammingHeuristic : public Heuristic
    {
    private:
        unsigned int estimateMinPathCostToTarget(const std::shared_ptr<Node> &node) const override;

    public:
        static std::string name();
    };
}

#endif //FIFTEEN_GAME_SOLVER_HAMMING_HEURISTIC_HPP
