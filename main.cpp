#include <iostream>
#include "graph.hpp"
#include "node.hpp"
#include "bfs_solver.hpp"
#include <memory>
#include "operation.hpp"
#include "dfs_solver.hpp"

using namespace fifteen;

int main() {
    std::vector<std::vector<u_int8_t>> gameBoard = {{1, 2, 3, 7},
                                                    {4, 5, 6, 11},
                                                    {8, 9, 14, 10},
                                                    {12, 13, 0, 15}};
    const auto initialState = std::make_shared<State>(gameBoard);
    const auto initialNode = std::make_shared<Node>(initialState);

    std::vector<Operation> operations = {Operation::DOWN, Operation::LEFT, Operation::UP, Operation::RIGHT};
    const auto solver = std::make_shared<DFSSolver>(operations, 20);
//    const auto solver = std::make_shared<BFSSolver>(operations);
    Graph graph(initialNode, solver);
    std::cout << graph.solution();
    return 0;
}
