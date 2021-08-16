set(SRCS
        1_two_sum.cpp
        2_add_two_numbers.cpp
        3_longest_substring_without_repeating_chars.cpp
        4_median_of_two_sorted_arrays.cpp
        5_longest_palindromic_substring.cpp
        14_longest_common_prefix.cpp
        15_3_sum.cpp
        16_3sum_closest.cpp
        17_letter_combinations_of_a_phone_number.cpp
        18_4_sum.cpp
        21_merge_two_sorted_lists.cpp
        22_generate_parentheses.cpp
        25_reverse_nodes_in_k_group.cpp
        33_search_in_rotated_sorted_array.cpp
        39_combination_sum.cpp
        40_combination_sum.cpp
        41_first_missing_positive.cpp
        42_trapping_rain_water.cpp
        45_jump_game_2.cpp
        46_permutations.cpp
        47_permutations_2.cpp
        49_group_anagrams.cpp
        50_power.cpp
        53_max_subarray.cpp
        54_spiral_matrix.cpp
        59_spiral_matrix_2.cpp
        62_unique_paths.cpp
        70_climbing_stairs.cpp
        72_edit_distance.cpp
        73_matrix_zeros.cpp
        76_minimum_window_substring.cpp
        77_combinations.cpp
        79_word_search.cpp
        90_subsets_2.cpp
        94_binary_tree_inorder_traversal.cpp
        98_validate_binary_search_tree.cpp
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
