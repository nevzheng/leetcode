set(SRCS
        300_longest_increasing_subsequence.cpp
        303_range_sum_query_immutable.cpp
        322_coin_change.cpp
        329_longest_increasing_path_in_a_matrix.cpp
        330_patching_array.cpp
        331_verify_preorder_serialization_binary_tree.cpp
        337_house_robber_3.cpp
        344_reverse_string.cpp
        347_top_k_frequent_elements.cpp
        377_combination_sum_iv.cpp
        394_decode_string.cpp
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
