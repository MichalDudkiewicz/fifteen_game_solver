cmake_minimum_required(VERSION 3.17)
project(fifteen_game_solver)

set(CMAKE_CXX_STANDARD 17)

add_executable(fifteen_game_solver main.cpp node.cpp operation.hpp state.cpp operation.cpp state.hpp graph.cpp solver.hpp solution.cpp bfs_solver.cpp blind_solver.cpp solver.cpp dfs_solver.cpp heuristic.hpp heuristic.cpp heuristic_solver.hpp hamming_heuristic.cpp manhattan_heuristic.cpp utils.cpp)
target_include_directories(fifteen_game_solver PUBLIC boost_1_66_0)