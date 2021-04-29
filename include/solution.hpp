#ifndef FIFTEEN_GAME_SOLVER_SOLUTION_HPP
#define FIFTEEN_GAME_SOLVER_SOLUTION_HPP

#include "node.hpp"
#include <memory>
#include <string>

namespace fifteen
{
    class Solution {
    public:
        Solution(const std::shared_ptr<Node> &solutionNode,
                 unsigned int openStatesNumber,
                 unsigned int closedStatesNumber,
                 unsigned int maxRecursionDepth,
                 long calculationMicroSecTime);

        Solution(unsigned int openStatesNumber,
                 unsigned int closedStatesNumber,
                 unsigned int maxRecursionDepth,
                 long calculationMicroSecTime);

        unsigned int pathCost() const;

        unsigned int visitedStatesNumber() const;

        unsigned int closedStatesNumber() const;

        const std::list<Operation>& path() const;

        const std::shared_ptr<Node>& initialNode() const;

        unsigned int maxRecursionDepth() const;

        long calculationMicroSecTime() const;

        bool solutionFound() const;

        friend std::ostream& operator<<(std::ostream& os, const Solution& solution);

    private:
        std::shared_ptr<Node> mInitialNode;
        unsigned int mPathCost;
        unsigned int mVisitedStatesNumber;
        unsigned int mClosedStatesNumber;
        std::list<Operation> mPath;
        unsigned int mMaxRecursionDepth;
        long mCalculationMicroSecTime;
        bool mSolutionFound;
    };
}

#endif //FIFTEEN_GAME_SOLVER_SOLUTION_HPP
