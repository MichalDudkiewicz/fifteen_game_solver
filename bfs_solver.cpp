#include <iostream>
#include "bfs_solver.hpp"

namespace fifteen
{
    BFSSolver::BFSSolver(const std::vector<Operation> &operationOrder) : BlindSolver(operationOrder)
    {
    }

    Solution BFSSolver::solve(const std::shared_ptr<Node> &initialNode) {
        auto nodeToCheck = initialNode;
        auto stateToCheck = initialNode->state();
        while(!isSolution(stateToCheck))
        {
            const auto neighbours = nodeToCheck->neighbours(mOperationOrder);
            for (const auto& neighbour : neighbours)
            {
                const auto neighbourState = neighbour->state();
                if (isSolution(neighbourState))
                {
                    Solution solution(neighbour, mOpenList.size(), mClosedList.size());
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
        Solution solution(nodeToCheck, mOpenList.size(), mClosedList.size());
        return solution;
    }
}