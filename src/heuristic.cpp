#include "heuristic.hpp"

namespace fifteen
{
    unsigned int Heuristic::estimatePathCostToTarget(const std::shared_ptr<Node> &node) const {
        const unsigned int currentPathCost = node->pathCost();
        return currentPathCost + estimateMinPathCostToTarget(node);
    }

    bool Heuristic::operator()(const std::shared_ptr<Node> &firstNode, const std::shared_ptr<Node> &secondNode) const {
        return estimatePathCostToTarget(firstNode) > estimatePathCostToTarget(secondNode);
    }
}

