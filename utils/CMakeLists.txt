# Define libraries
# Add Utils
add_library(utils src/utils.cpp)
target_link_libraries(utils CONAN_PKG::fmt)
target_include_directories(utils PUBLIC include)
# Add Union Find
add_library(union_find src/UnionFind.cpp)
target_include_directories(union_find PUBLIC include)
# Add Tarjan Solver
add_library(tarjan_solver src/TarjanSolver.cpp)
target_include_directories(tarjan_solver PUBLIC include)
# Add Trie
add_library(trie src/Trie.cpp)
target_include_directories(trie PUBLIC include)
