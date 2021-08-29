set(SRCS
        915_partition_array_into_disjoint_intervals.cpp
        926_flip_string_to_monotone.cpp
        927_three_equal_parts.cpp
        932_beautiful_array.cpp
        937_reorder_data_in_log_files.cpp
        954_array_of_doubled_pairs.cpp
        957_prison_cell_after_n_days.cpp
        968_binary_tree_cameras.cpp
        977_squares_of_a_sorted_array.cpp
        987_vertical_order_traversal_of_a_binary_tree.cpp
        988_smallest_string_starting_from_leaf.cpp
        994_rotting_oranges.cpp
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
