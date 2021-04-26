#include <chrono>
#include "dfs_solver.hpp"
#include <iostream>

namespace fifteen
{

    DFSSolver::DFSSolver(const std::vector<Operation> &operationOrder, unsigned int recursionDepthLimit)
    : BlindSolver(operationOrder),
    mRecursionDepthLimit(recursionDepthLimit)
    {
    }

    Solution DFSSolver::solve(const std::shared_ptr<Node> &initialNode) {
        auto nodeToCheck = initialNode;
        auto stateToCheck = initialNode->state();
        unsigned int maxRecursionDepth = 0;
        std::vector<Operation> reversedOperationOrder (mOperationOrder.rbegin(), mOperationOrder.rend());
        auto started = std::chrono::high_resolution_clock::now();
        while(!isSolution(stateToCheck))
        {
            const auto operation = nodeToCheck->operationOnParent();
            const auto neighbours = nodeToCheck->neighbours(reversedOperationOrder);
            const unsigned int nodeDepth = nodeToCheck->pathCost();
            const unsigned int neighboursDepth = nodeDepth + 1;
            maxRecursionDepth = std::max(maxRecursionDepth, neighboursDepth);
            for (const auto& neighbour : neighbours)
            {
                const auto neighbourState = neighbour->state();
                if (isSolution(neighbourState))
                {
                    auto finished = std::chrono::high_resolution_clock::now();
                    const auto calculationMicroSecTime = std::chrono::duration_cast<std::chrono::microseconds>(finished-started).count();
                    Solution solution(neighbour, mOpenList.size(), mClosedList.size(), maxRecursionDepth, calculationMicroSecTime);
                    return solution;
                }
                else if (!isClosed(*neighbour) && neighboursDepth < mRecursionDepthLimit)
                {
                    mClosedList.insert(*nodeToCheck);
                    mOpenList.push_back(neighbour);
                }
            }
            nodeToCheck = mOpenList.back();
            mOpenList.pop_back();
            stateToCheck = nodeToCheck->state();
        }
        auto finished = std::chrono::high_resolution_clock::now();
        const auto calculationMicroSecTime = std::chrono::duration_cast<std::chrono::microseconds>(finished-started).count();
        Solution solution(nodeToCheck, mOpenList.size(), mClosedList.size(), maxRecursionDepth, calculationMicroSecTime);
        return solution;
    }
}