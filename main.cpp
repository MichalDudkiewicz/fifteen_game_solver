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
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include "type_defs.hpp"

using namespace fifteen;

std::vector<Operation> parseOperations(const std::string& operations)
{
    std::vector<Operation> operationsParsed;
    operationsParsed.reserve(4);
    for(const char& c : operations) {
        operationsParsed.push_back(fromChar(c));
    }
    return operationsParsed;
}

/*
 * Program do rozwiązywania fifteen puzzle o dowolnym prostokątnym rozmiarze.
 *
 * Instrukcja obsługi programu oraz opis parametrów wywołania są dostępne tutaj: https://ftims.edu.p.lodz.pl/mod/page/view.php?id=59205
 *
 * Uwaga: ostatnie dwa parametry wywołania nie są obowiązkowe. Ich podanie nic nie zmienia w działaniu programu.
 *
 * Program należy uruchomić w katalogu, w którym znajduje się podkatalog o nazwie 'unsolved'.
 * W razie potrzeby należy utworzyć go ręcznie. Z niego pobierane są układy w formie plików txt do rozwiązania.
 * Układy rozwiązane są zapisywane w bieżącym katalogu, w którym uruchomiony jest program.
 *
 */
int main(int argc, char **argv) {
    if (argc < 4)
    {
        throw std::runtime_error("all first 3 arguments are obligatory");
    }

    std::string inputFileNameTxt = argv[3];
    std::string inputFileName = inputFileNameTxt.substr(0, inputFileNameTxt.find('.'));
    std::string inputSolver = argv[1];
    std::string inputSolverParam = argv[2];

    std::string line;
    std::ifstream puzzleToBeSolvedFile ("unsolved/" + inputFileNameTxt);
    unsigned int rowsNumber = 0;
    unsigned int columnsNumber = 0;

    std::vector<std::vector<u_int8_t>> gameBoard;

    if (puzzleToBeSolvedFile.is_open())
    {
        getline (puzzleToBeSolvedFile,line);
        std::vector<std::string> row;
        row.reserve(2);
        boost::split(row, line, boost::is_any_of(" "));
        rowsNumber = std::stoi(row.front());
        columnsNumber = std::stoi(row.back());
        row.clear();
        row.reserve(columnsNumber);
        gameBoard.reserve(rowsNumber);
        unsigned int rowCounter = 0;
        unsigned int columnCounter = 0;
        while ( getline (puzzleToBeSolvedFile,line) )
        {
            rowCounter++;
            boost::split(row, line, boost::is_any_of(" "));
            std::vector<uint8_t> rowInt;
            rowInt.reserve(columnsNumber);
            for (const auto& elemStr : row)
            {
                rowInt.push_back(std::stoi(elemStr));
                columnCounter++;
            }
            gameBoard.push_back(rowInt);
            rowInt.clear();
            row.clear();
            if (columnCounter != columnsNumber)
            {
                throw std::runtime_error("incorrect number of columns");
            }
            columnCounter = 0;
        }
        puzzleToBeSolvedFile.close();
        if (rowCounter != rowsNumber)
        {
            throw std::runtime_error("incorrect number of rows");
        }
    }
    else
    {
        throw std::runtime_error("unable to open the file specified as the third param, which is: ./unsolved/" + inputFileNameTxt);
    }

    const auto initialState = std::make_shared<State>(gameBoard);
    const auto initialNode = std::make_shared<Node>(initialState);

    std::shared_ptr<Solver> solver;
    std::ostringstream solverName;
    if (inputSolver == "dfs")
    {
        const auto operations = parseOperations(inputSolverParam);
        const unsigned int maxRecursionDepth = 20;
        solver = std::make_shared<DFSSolver>(operations, maxRecursionDepth);
        solverName << *(std::dynamic_pointer_cast<DFSSolver>(solver));
    }
    else if (inputSolver == "bfs")
    {
        const auto operations = parseOperations(inputSolverParam);
        solver = std::make_shared<BFSSolver>(operations);
        solverName << *(std::dynamic_pointer_cast<BFSSolver>(solver));
    }
    else if (inputSolver == "astr")
    {
        if (inputSolverParam == "hamm")
        {
            solver = std::make_shared<HeuristicSolver<HammingHeuristic>>();
            solverName << *(std::dynamic_pointer_cast<HeuristicSolver<HammingHeuristic>>(solver));
        }
        else if (inputSolverParam == "manh")
        {
            solver = std::make_shared<HeuristicSolver<ManhattanHeuristic>>();
            solverName << *(std::dynamic_pointer_cast<HeuristicSolver<ManhattanHeuristic>>(solver));
        }
        else
        {
            throw std::runtime_error("incorrect second argument");
        }
    }
    else
    {
        throw std::runtime_error("incorrect first argument");
    }

    std::ostringstream fileNameStream, fileNameSolStream, fileNameStatsStream;
    fileNameStream << inputFileName << '_' << solverName.str() << '_';
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
    else std::cout << "Unable to open sol file. Try running with admin privileges." << std::endl;

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
    else std::cout << "Unable to open stats file. Try running with admin privileges." << std::endl;

    return 0;
}
