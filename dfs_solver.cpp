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
        auto parent = initialNode;
        auto stateToCheck = initialNode->state();
        unsigned int maxRecursionDepth = 0;
        if (isSolution(stateToCheck))
        {
            const auto calculationMicroSecTime = 0;
            Solution solution(parent, mOpenList.size(), mClosedList.size(), maxRecursionDepth, calculationMicroSecTime);
            return solution;
        }
        std::vector<Operation> reversedOperationOrder (mOperationOrder.rbegin(), mOperationOrder.rend());
        mClosedList.insert(*parent);
        auto started = std::chrono::high_resolution_clock::now();
        while(mOpenList.size() >= 0)
        {
            const auto operation = parent->operationOnParent();
            const auto children = parent->neighbours(reversedOperationOrder);
            const unsigned int parentDepth = parent->pathCost();
            const unsigned int childrenDepth = parentDepth + 1;
            maxRecursionDepth = std::max(maxRecursionDepth, childrenDepth);
            for (const auto& child : children)
            {
                const auto childState = child->state();
                if (isSolution(childState))
                {
                    auto finished = std::chrono::high_resolution_clock::now();
                    const auto calculationMicroSecTime = std::chrono::duration_cast<std::chrono::microseconds>(finished-started).count();
                    Solution solution(child, mOpenList.size(), mClosedList.size(), maxRecursionDepth, calculationMicroSecTime);
                    return solution;
                }
                else if (!isClosed(*child) && childrenDepth < mRecursionDepthLimit)
                {
                    mClosedList.insert(*child);
                    mOpenList.push_back(child);
                }
            }
            parent = mOpenList.back();
            mOpenList.pop_back();
        }
        throw std::runtime_error("no solution found for specified initial state and recursion depth. Try simplyfing the board to solve or changing recursion depth");
    }
}