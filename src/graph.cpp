#include "graph.hpp"

namespace fifteen
{
    Solution fifteen::Graph::solution() const {
        return mSolver->solve(mInitialNode);
    }
}
