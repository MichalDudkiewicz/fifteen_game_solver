#include <iostream>
#include "bfs_solver.hpp"
#include <chrono>

namespace fifteen
{
    BFSSolver::BFSSolver(const std::vector<Operation> &operationOrder) : BlindSolver(operationOrder)
    {
    }

    Solution BFSSolver::solve(const std::shared_ptr<Node> &initialNode) {
        auto nodeToCheck = initialNode;
        auto stateToCheck = initialNode->state();
        unsigned int maxRecursionDepth = 0;
        auto started = std::chrono::high_resolution_clock::now();
        while(!isSolution(stateToCheck))
        {
            const auto neighbours = nodeToCheck->neighbours(mOperationOrder);
            for (const auto& neighbour : neighbours)
            {
                const auto neighbourState = neighbour->state();
                if (isSolution(neighbourState))
                {
                    auto finished = std::chrono::high_resolution_clock::now();
                    const auto calculationMsTime = std::chrono::duration_cast<std::chrono::milliseconds>(finished-started).count();
                    maxRecursionDepth = std::max(maxRecursionDepth, neighbour->pathCost());
                    Solution solution(neighbour, mOpenList.size(), mClosedList.size(), maxRecursionDepth, calculationMsTime);
                    return solution;
                }
                else if (!isOpened(neighbour) && !isClosed(*neighbour))
                {
                    mOpenList.push_back(neighbour);
                }
            }
            mClosedList.insert(*nodeToCheck);
            nodeToCheck = mOpenList.front();
            mOpenList.pop_front();
            stateToCheck = nodeToCheck->state();
        }
        auto finished = std::chrono::high_resolution_clock::now();
        const auto calculationMsTime = std::chrono::duration_cast<std::chrono::milliseconds>(finished-started).count();
        Solution solution(nodeToCheck, mOpenList.size(), mClosedList.size(), maxRecursionDepth, calculationMsTime);
        return solution;
    }
}