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

        template<class Heuristic2>
        friend std::ostream &operator<<(std::ostream &os, const HeuristicSolver& solver);

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
        // no solution found
        auto finished = std::chrono::high_resolution_clock::now();
        const auto calculationMicroSecTime = std::chrono::duration_cast<std::chrono::microseconds>(finished-started).count();
        Solution solution(mOpenList.size(), mClosedList.size(), maxRecursionDepth, calculationMicroSecTime);
        return solution;
    }

    template<class Heuristic>
    std::ostream &operator<<(std::ostream &os, const HeuristicSolver<Heuristic> &manhattanSolver) {
        os << "astr_" << Heuristic::name();
        return os;
    }
}


#endif //FIFTEEN_GAME_SOLVER_HEURISTIC_SOLVER_HPP
