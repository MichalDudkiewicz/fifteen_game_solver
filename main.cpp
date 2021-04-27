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
#include <fstream>
#include <string>
#include <ostream>
#include "utils.hpp"

using namespace fifteen;

int main() {
    std::string inputFileName = "4x4_01_0001";

    std::vector<std::vector<u_int8_t>> gameBoard = {{1, 2, 3, 0},
                                                    {5, 6, 7, 4},
                                                    {9, 10, 11, 8},
                                                    {13, 14, 15, 12}};

    const auto initialState = std::make_shared<State>(gameBoard);
    const auto initialNode = std::make_shared<Node>(initialState);

    std::vector<Operation> operations = {Operation::DOWN, Operation::LEFT, Operation::UP, Operation::RIGHT};

    const auto solver = std::make_shared<DFSSolver>(operations, 20);

//    const auto solver = std::make_shared<BFSSolver>(operations);

//    const auto solver = std::make_shared<HeuristicSolver<HammingHeuristic>>();

//    const auto solver = std::make_shared<HeuristicSolver<ManhattanHeuristic>>();

    std::ostringstream fileNameStream;
    fileNameStream << inputFileName << '_' << *solver << '_' << "sol.txt";
    std::string fileName = fileNameStream.str();
    Graph graph(initialNode, solver);
    try {
        const auto solution = graph.solution();
        std::cout << solution << std::endl;
        std::ofstream myfile (fileName);
        if (myfile.is_open())
        {
            myfile << solution.pathCost() << "\n";
            myfile << solution.path() << "\n";
            myfile.close();
        }
        else std::cout << "Unable to open file" << std::endl;
    }
    catch (const std::runtime_error& iKnowThisIsUnproffesional) {
        std::cout<<std::endl<<"no solution found!" << std::endl;
        std::ofstream myfile (fileName);
        if (myfile.is_open())
        {
            myfile << -1 << "\n";
            myfile.close();
        }
        else std::cout << "Unable to open file" << std::endl;
    }

    return 0;
}
