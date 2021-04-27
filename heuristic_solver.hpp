#ifndef FIFTEEN_GAME_SOLVER_HEURISTIC_SOLVER_HPP
#define FIFTEEN_GAME_SOLVER_HEURISTIC_SOLVER_HPP

#include <queue>
#include <chrono>
#include "solver.hpp"
#include "heuristic.hpp"
#include "solution.hpp"

namespace fifteen
{
    template <class Heuristic>
    class HeuristicSolver : public Solver {
    public:
        Solution solve(const std::shared_ptr<Node> &rootNode) override;

    private:
        std::priority_queue<std::shared_ptr<Node>, std::deque<std::shared_ptr<Node>>, Heuristic> mOpenList;
    };

    template <class Heuristic>
    Solution HeuristicSolver<Heuristic>::solve(const std::shared_ptr<Node> &rootNode) {
        auto parent = rootNode;
        auto stateToCheck = rootNode->state();
        unsigned int maxRecursionDepth = 0;
        if (isSolution(stateToCheck))
        {
            const auto calculationMicroSecTime = 0;
            Solution solution(parent, mOpenList.size(), mClosedList.size(), maxRecursionDepth, calculationMicroSecTime);
            return solution;
        }
        mClosedList.insert(*parent);
        const std::vector<Operation> operationOrder = {Operation::UP, Operation::RIGHT, Operation::DOWN, Operation::LEFT};
        auto started = std::chrono::high_resolution_clock::now();
        while(true)
        {
            const auto children = parent->children(operationOrder);
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
                else if (!isClosed(*child))
                {
                    mClosedList.insert(*child);
                    mOpenList.push(child);
                }
            }
            if (mOpenList.empty())
            {
                break;
            }
            parent = mOpenList.top();
            mOpenList.pop();
        }
        throw std::runtime_error("no solution found for specified initial state and recursion depth. Try simplyfing the board.");
    }
}


#endif //FIFTEEN_GAME_SOLVER_HEURISTIC_SOLVER_HPP
