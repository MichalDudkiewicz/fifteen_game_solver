#include <iostream>
#include "graph.hpp"
#include "node.hpp"
#include "bfs_solver.hpp"
#include <memory>
#include "operation.hpp"
#include "dfs_solver.hpp"

using namespace fifteen;

int main() {
    std::vector<std::vector<u_int8_t>> gameBoard = {{1, 5, 2, 3},
                                                    {4, 6, 10, 7},
                                                    {8, 9, 11, 15},
                                                    {12, 13, 0, 14}};
    const auto initialState = std::make_shared<State>(gameBoard);
    const auto initialNode = std::make_shared<Node>(initialState);

    std::vector<Operation> operations = {Operation::DOWN, Operation::LEFT, Operation::UP, Operation::RIGHT};
    const auto solver = std::make_shared<DFSSolver>(operations, 20);
//    const auto solver = std::make_shared<BFSSolver>(operations);
    Graph graph(initialNode, solver);
    std::cout << graph.solution();
    return 0;
}
