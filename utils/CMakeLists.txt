include_directories(include)

# Define libraries
# Add Utils
add_library(utils src/utils.cpp)
target_link_libraries(utils CONAN_PKG::fmt)
# Add Union Find
add_library(union_find src/UnionFind.cpp)
# Add Tarjan Solver
add_library(tarjan_solver src/TarjanSolver.cpp)
# Add Trie
add_library(trie src/Trie.cpp)
