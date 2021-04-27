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

    std::vector<std::vector<u_int8_t>> gameBoard = {{1, 2, 0, 3},
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

    std::ostringstream fileNameStream, fileNameSolStream, fileNameStatsStream;
    fileNameStream << inputFileName << '_' << *solver << '_';
    std::string fileName = fileNameStream.str();
    fileNameSolStream << fileName << "sol.txt";
    std::string fileNameSol = fileNameSolStream.str();
    fileNameStatsStream << fileName << "stats.txt";
    std::string fileNameStats = fileNameStatsStream.str();
    Graph graph(initialNode, solver);


    const auto solution = graph.solution();
    std::cout << solution << std::endl;
    std::ofstream solFile (fileNameSol);
    if (solFile.is_open())
    {
        if (solution.solutionFound())
        {
            solFile << solution.pathCost() << "\n";
            solFile << solution.path() << "\n";
        }
        else
        {
            std::cout<<std::endl<<"no solution found!" << std::endl;
            solFile << -1 << "\n";
        }
        solFile.close();
    }
    else std::cout << "Unable to open sol file" << std::endl;

    std::ofstream statsFile (fileNameStats);
    if (statsFile.is_open())
    {
        statsFile << (solution.solutionFound() ? solution.pathCost() : -1) << "\n";
        statsFile << solution.visitedStatesNumber() << "\n";
        statsFile << solution.closedStatesNumber() << "\n";
        statsFile << solution.maxRecursionDepth() << "\n";
        statsFile << (float)solution.calculationMicroSecTime()/1000.0f << "\n";
        statsFile.close();
    }
    else std::cout << "Unable to open stats file" << std::endl;

    return 0;
}
