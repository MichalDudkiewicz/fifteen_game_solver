#ifndef FIFTEEN_GAME_SOLVER_SOLUTION_HPP
#define FIFTEEN_GAME_SOLVER_SOLUTION_HPP

#include "node.hpp"
#include <memory>

namespace fifteen
{
    class Solution {
    public:
        Solution(const std::shared_ptr<Node> &solutionNode, unsigned int openStatesNumber, unsigned int closedStatesNumber);

        unsigned int pathCost() const;

        unsigned int visitedStatesNumber() const;

        unsigned int closedStatesNumber() const;

        const std::list<Operation>& path() const;

        const std::shared_ptr<Node>& initialNode() const;

        friend std::ostream& operator<<(std::ostream& os, const Solution& solution);

    private:
        std::shared_ptr<Node> mInitialNode;
        unsigned int mPathCost;
        unsigned int mVisitedStatesNumber;
        unsigned int mClosedStatesNumber;
        std::list<Operation> mPath;
//        unsigned int mMaxRecursionDepth;
//        mCalculationTime
    };
}

#endif //FIFTEEN_GAME_SOLVER_SOLUTION_HPP
