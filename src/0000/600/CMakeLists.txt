set(SRCS
        600_non_negative_integers_without_consecutive_ones.cpp
        611_valid_triangle_number.cpp
        633_sum_of_squares.cpp
        639_decode_ways_2.cpp
        653_two_sum_iv.cpp
        662_maximum_width_of_binary_tree.cpp
        663_equal_tree_partition.cpp
        677_map_sum_pairs.cpp
        684_redundant_connection.cpp
        685_redundant_connection_2.cpp
        692_top_k_frequent_words.cpp
        )
# Add Catch2 Definition
include(Catch)

# Create Executables
foreach (SRC ${SRCS})
    get_filename_component(BIN ${SRC} NAME_WE) # Grab Filename wo path and extension
    add_executable(${BIN} ${SRC} ../../main.cpp) # Catch main should be its own file to avoid recompilation
    target_link_libraries(${BIN} PRIVATE CONAN_PKG::catch2 CONAN_PKG::fmt utils trie union_find tarjan_solver)
    catch_discover_tests(${BIN})
endforeach ()
