set(SRCS
        508_most_frequent_subtree_sum.cpp
        513_find_bottom_left_tree_value.cpp
        516_longest_palindromic_subsequence.cpp
        537_complex_number_multiplication.cpp
        542_01_matrix.cpp
        543_diameter_of_binary_tree.cpp
        546_remove_boxes.cpp
        572_subtree_of_another_tree.cpp
        )
# Add Catch2 Definition
include(Catch)

# Create Executables
foreach (SRC ${SRCS})
    get_filename_component(BIN ${SRC} NAME_WE) # Grab Filename w/o path and extension
    add_executable(${BIN} ${SRC} ../../main.cpp) # Catch main should be its own file to avoid recompilation
    target_link_libraries(${BIN} PRIVATE CONAN_PKG::catch2 CONAN_PKG::fmt utils trie union_find tarjan_solver)
    catch_discover_tests(${BIN})
endforeach ()
