cmake_minimum_required(VERSION 3.17)
project(fifteen_game_solver)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a .lib")
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS "-static")
add_executable(fifteen_game_solver main.cpp node.cpp operation.hpp state.cpp operation.cpp state.hpp graph.cpp solver.hpp solution.cpp bfs_solver.cpp blind_solver.cpp solver.cpp dfs_solver.cpp heuristic.hpp heuristic.cpp heuristic_solver.hpp hamming_heuristic.cpp manhattan_heuristic.cpp utils.cpp type_defs.hpp)
target_include_directories(fifteen_game_solver PUBLIC boost_1_66_0)