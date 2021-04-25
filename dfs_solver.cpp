#include <chrono>
#include "dfs_solver.hpp"
#include <boost/range/adaptor/reversed.hpp>
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
        auto started = std::chrono::high_resolution_clock::now();
        while(!isSolution(stateToCheck))
        {
            const auto operation = nodeToCheck->operationOnParent();
            const auto neighbours = nodeToCheck->neighbours(mOperationOrder);
            const unsigned int nodeDepth = nodeToCheck->pathCost();
            const unsigned int neighboursDepth = nodeDepth + 1;
            maxRecursionDepth = std::max(maxRecursionDepth, neighboursDepth);
            for (const auto& neighbour : boost::adaptors::reverse(neighbours))
            {
                const auto neighbourState = neighbour->state();
                if (isSolution(neighbourState))
                {
                    auto finished = std::chrono::high_resolution_clock::now();
                    const auto calculationMicroSecTime = std::chrono::duration_cast<std::chrono::microseconds>(finished-started).count();
                    Solution solution(neighbour, mOpenList.size(), mClosedList.size(), maxRecursionDepth, calculationMicroSecTime);
                    return solution;
                }
                else if (!isOpened(neighbour) && !isClosed(*neighbour) && neighboursDepth < mRecursionDepthLimit)
                {
                    mOpenList.push_back(neighbour);
                }
            }
            mClosedList.insert(*nodeToCheck);
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