cmake_minimum_required(VERSION 3.17)
project(fifteen_game_solver)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a .lib")
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS "-static")

set(SOURCE_FILES
        src/node.cpp
        src/state.cpp
        src/operation.cpp
        src/graph.cpp
        src/solution.cpp
        src/bfs_solver.cpp
        src/blind_solver.cpp
        src/solver.cpp
        src/dfs_solver.cpp
        src/heuristic.cpp
        src/hamming_heuristic.cpp
        src/manhattan_heuristic.cpp
        src/utils.cpp
        )

set(INCLUDE_FILES
        include/node.hpp
        include/state.hpp
        include/operation.hpp
        include/graph.hpp
        include/solution.hpp
        include/bfs_solver.hpp
        include/blind_solver.hpp
        include/solver.hpp
        include/dfs_solver.hpp
        include/heuristic.hpp
        include/heuristic_solver.hpp
        include/manhattan_heuristic.hpp
        include/hamming_heuristic.hpp
        include/utils.hpp
        )

add_executable(fifteen_game_solver main.cpp ${SOURCE_FILES} ${INCLUDE_FILES})
target_include_directories(fifteen_game_solver PUBLIC thirdparty/boost_1_66_0 include)