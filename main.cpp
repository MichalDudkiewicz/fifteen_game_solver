#include <iostream>
#include "graph.hpp"
#include "node.hpp"
#include "bfs_solver.hpp"
#include <memory>
#include "operation.hpp"
#include <iostream>

using namespace fifteen;

int main() {
    std::vector<std::vector<u_int8_t>> gameBoard = {{4, 1, 2, 3},
                                                    {8, 5, 6, 7},
                                                    {12, 9, 10, 0},
                                                    {13, 14, 15, 11}};
    const auto initialState = std::make_shared<State>(gameBoard);
    const auto initialNode = std::make_shared<Node>(initialState);

    std::vector<Operation> operations = {Operation::UP, Operation::RIGHT, Operation::DOWN, Operation::LEFT};
    const auto bfsSolver = std::make_shared<BFSSolver>(operations);
    Graph graph(initialNode, bfsSolver);
    std::cout << graph.solution();
    return 0;
}
