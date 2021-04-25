#include <iostream>
#include "graph.hpp"
#include "node.hpp"
#include "bfs_solver.hpp"
#include <memory>
#include "operation.hpp"
#include "dfs_solver.hpp"

using namespace fifteen;

int main() {
    std::vector<std::vector<u_int8_t>> gameBoard = {{1, 2, 0, 3, 4},
                                                    {5, 6, 7, 8, 9},
                                                    {10, 11, 12, 13, 14},
                                                    {15, 16, 17, 18, 19}};
    const auto initialState = std::make_shared<State>(gameBoard);
    const auto initialNode = std::make_shared<Node>(initialState);

    std::vector<Operation> operations = {Operation::DOWN, Operation::UP, Operation::LEFT, Operation::RIGHT};
    const auto solver = std::make_shared<DFSSolver>(operations, 10);
//    const auto solver = std::make_shared<BFSSolver>(operations);
    Graph graph(initialNode, solver);
    std::cout << graph.solution();
    return 0;
}
