#include "solution.hpp"

namespace fifteen
{
    Solution::Solution(const std::shared_ptr<Node> &solutionNode, unsigned int openStatesNumber, unsigned int closedStatesNumber, unsigned int maxRecursionDepth, long calculationMsTime)
    : mPathCost(solutionNode->pathCost()),
    mVisitedStatesNumber(openStatesNumber + closedStatesNumber),
    mClosedStatesNumber(closedStatesNumber),
    mMaxRecursionDepth(maxRecursionDepth),
    mCalculationMsTime(calculationMsTime)
    {
        auto node = solutionNode;
        while (node->parent())
        {
            mPath.push_front(node->operationOnParent().value());
            node = node->parent();
        }
        mInitialNode = node;
    }

    unsigned int Solution::pathCost() const {
        return mPathCost;
    }

    unsigned int Solution::visitedStatesNumber() const {
        return mVisitedStatesNumber;
    }

    unsigned int Solution::closedStatesNumber() const {
        return mClosedStatesNumber;
    }

    const std::list<Operation> &Solution::path() const {
        return mPath;
    }

    const std::shared_ptr<Node> &Solution::initialNode() const {
        return mInitialNode;
    }

    std::ostream &operator<<(std::ostream &os, const Solution &solution) {
        os << "Solution: ";
        for (const auto& operation: solution.path())
        {
            os << operation;
        }
        os << std::endl;

        os << "Path cost: " << solution.mPathCost << std::endl
        << "Closed states number: " << solution.mClosedStatesNumber << std::endl
        << "Visited states number: " << solution.mVisitedStatesNumber << std::endl
        << "Max recursion depth: " << solution.mMaxRecursionDepth << std::endl
        << "Calculation time [ms]: " << solution.mCalculationMsTime << std::endl;
        return os;
    }
}