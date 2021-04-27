#include <iostream>
#include "graph.hpp"
#include "node.hpp"
#include "bfs_solver.hpp"
#include <memory>
#include "operation.hpp"
#include "dfs_solver.hpp"
#include "hamming_heuristic.hpp"
#include "heuristic_solver.hpp"
#include "manhattan_heuristic.hpp"

using namespace fifteen;

int main() {
    std::vector<std::vector<u_int8_t>> gameBoard = {{1, 2, 3, 0},
                                                    {5, 6, 7, 4},
                                                    {9, 10, 11, 8},
                                                    {13, 14, 15, 12}};
    const auto initialState = std::make_shared<State>(gameBoard);
    const auto initialNode = std::make_shared<Node>(initialState);

    std::vector<Operation> operations = {Operation::DOWN, Operation::LEFT, Operation::UP, Operation::RIGHT};

//    const auto solver = std::make_shared<DFSSolver>(operations, 20);

//    const auto solver = std::make_shared<BFSSolver>(operations);

//    const auto solver = std::make_shared<HeuristicSolver<HammingHeuristic>>();

    const auto solver = std::make_shared<HeuristicSolver<ManhattanHeuristic>>();

    Graph graph(initialNode, solver);
    std::cout << graph.solution();
    return 0;
}
