#include <chrono>
#include "dfs_solver.hpp"
#include <iostream>
#include "utils.hpp"

namespace fifteen
{

    DFSSolver::DFSSolver(const std::vector<Operation> &operationOrder, unsigned int recursionDepthLimit)
    : BlindSolver(operationOrder),
    mRecursionDepthLimit(recursionDepthLimit)
    {
    }

    Solution DFSSolver::solve(const std::shared_ptr<Node> &rootNode) {
        auto parent = rootNode;
        auto stateToCheck = rootNode->state();
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
        while(true)
        {
            const auto children = parent->children(reversedOperationOrder);
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
            if (mOpenList.empty())
            {
                break;
            }
            parent = mOpenList.back();
            mOpenList.pop_back();
        }
        // no solution found
        auto finished = std::chrono::high_resolution_clock::now();
        const auto calculationMicroSecTime = std::chrono::duration_cast<std::chrono::microseconds>(finished-started).count();
        Solution solution(mOpenList.size(), mClosedList.size(), maxRecursionDepth, calculationMicroSecTime);
        return solution;
    }

    std::ostream &operator<<(std::ostream &os, const DFSSolver &solver) {
        os << "dfs_" << solver.mOperationOrder;
        return os;
    }
}