#ifndef FIFTEEN_GAME_SOLVER_SOLUTION_HPP
#define FIFTEEN_GAME_SOLVER_SOLUTION_HPP

namespace fifteen
{
    class Solution {
    public:
        Solution(unsigned int pathCost);

        unsigned int pathCost() const;
    private:
        unsigned int mPathCost;
    };
}

#endif //FIFTEEN_GAME_SOLVER_SOLUTION_HPP
