#include <iostream>
#include "graph.hpp"
#include "node.hpp"
#include "bfs_solver.hpp"
#include <memory>
#include "operation.hpp"
#include <iostream>

using namespace fifteen;

int main() {
    std::vector<std::vector<u_int8_t>> gameBoard = {{1, 5, 2, 3},
                                                    {4, 9, 6, 7},
                                                    {8, 10, 11, 15},
                                                    {12, 0, 13, 14}};
    const auto initialState = std::make_shared<State>(gameBoard);
    const auto initialNode = std::make_shared<Node>(initialState);

    std::vector<Operation> operations = {Operation::UP, Operation::RIGHT, Operation::DOWN, Operation::LEFT};
    const auto bfsSolver = std::make_shared<BFSSolver>(operations);
    Graph graph(initialNode, bfsSolver);
    std::cout << graph.solution();
    return 0;
}
