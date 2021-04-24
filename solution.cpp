#include "solution.hpp"

namespace fifteen
{
    Solution::Solution(unsigned int pathCost)
    : mPathCost(pathCost)
    {

    }

    unsigned int Solution::pathCost() const {
        return mPathCost;
    }
}