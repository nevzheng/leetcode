set(SRCS
        0000/000/1_two_sum.cpp
        0000/000/2_add_two_numbers.cpp
        0000/000/4_median_of_two_sorted_arrays.cpp
        0000/000/14_longest_common_prefix.cpp
        0000/000/15_3_sum.cpp
        0000/000/16_3sum_closest.cpp
        0000/000/17_letter_combinations_of_a_phone_number.cpp
        0000/000/18_4_sum.cpp
        0000/000/22_generate_parentheses.cpp
        0000/000/25_reverse_nodes_in_k_group.cpp
        0000/000/33_search_in_rotated_sorted_array.cpp
        0000/000/39_combination_sum.cpp
        0000/000/40_combination_sum.cpp
        0000/000/41_first_missing_positive.cpp
        0000/000/42_trapping_rain_water.cpp
        0000/000/45_jump_game_2.cpp
        0000/000/50_power.cpp
        0000/000/53_max_subarray.cpp
        0000/000/79_word_search.cpp
        0000/000/90_subsets_2.cpp

        0000/100/105_construct_binary_tree_from_preorder_and_inorder_traversal.cpp
        0000/100/108_convert_sorted_array_to_binary_search_tree.cpp
        0000/100/110_balanced_binary_tree.cpp
        0000/100/114_flatten_binary_tree_to_linked_list.cpp
        0000/100/116_populating_next_right_pointers_in_each_node_1.cpp
        0000/100/117_populating_next_right_pointers_in_each_node_2.cpp
        0000/100/124_binary_tree_max_path_value.cpp
        0000/100/126_word_ladder2.cpp
        0000/100/127_word_ladder.cpp
        0000/100/133_clone_graph.cpp
        0000/100/138_copy_list_with_random_pointer.cpp
        0000/100/139_word_break.cpp
        0000/100/140_word_break_2.cpp
        0000/100/146_lru_cache.cpp
        0000/100/162_find_peak_element.cpp
        0000/100/167_two_sum_2.cpp
        0000/100/174_dungeon_game.cpp
        0000/100/198_house_robber.cpp
        0000/100/199_binary_tree_right_side_view.cpp

        0000/200/205_isomorphic_strings.cpp
        0000/200/207_course_schedule.cpp
        0000/200/210_course_schedule_ii.cpp
        0000/200/212_word_search_ii.cpp
        0000/200/213_house_robber_2.cpp
        0000/200/216_combination_sum_3.cpp
        0000/200/221_maximal_square.cpp
        0000/200/268_missing_number.cpp
        0000/200/269_alien_dictionary.cpp
        0000/200/295_find_median_from_data_stream.cpp

        0000/300/337_house_robber_3.cpp
        0000/300/347_top_k_frequent_elements.cpp
        0000/300/377_combination_sum_iv.cpp
        0000/300/394_decode_string.cpp

        0000/400/416_partition_equal_subset_sum.cpp
        0000/400/427_concatenated_words.cpp

        0000/500/508_most_frequent_subtree_sum.cpp
        0000/500/513_find_bottom_left_tree_value.cpp
        0000/500/516_longest_palindromic_subsequence.cpp
        0000/500/542_01_matrix.cpp
        0000/500/543_diameter_of_binary_tree.cpp

        0000/600/600_non_negative_integers_without_consecutive_ones.cpp
        0000/600/611_valid_triangle_number.cpp
        0000/600/662_maximum_width_of_binary_tree.cpp
        0000/600/677_map_sum_pairs.cpp
        0000/600/684_redundant_connection.cpp
        0000/600/685_redundant_connection_2.cpp

        0000/700/703_kth_largest_element_in_a_stream.cpp
        0000/700/785_is_graph_bipartite.cpp
        0000/700/787_cheapest_flights_within_k_stops.cpp

        0000/800/814_binary_tree_pruning.cpp
        0000/800/827_making_a_large_island.cpp
        0000/800/838_push_dominoes.cpp
        0000/800/841_keys_and_rooms.cpp
        0000/800/886_possible_bipartition.cpp

        0000/900/915_partition_array_into_disjoint_intervals.cpp
        0000/900/927_three_equal_parts.cpp
        0000/900/932_beautiful_array.cpp
        0000/900/968_binary_tree_cameras.cpp
        0000/900/987_vertical_order_traversal_of_a_binary_tree.cpp
        0000/900/988_smallest_string_starting_from_leaf.cpp

        1000/1008_construct_binary_search_tree_from_preorder_traversal.cpp
        1000/1041_robot_bounded_in_circle.cpp
        1000/1046_last_stone_weight.cpp
        1000/1056_confusing_number.cpp
        1000/1057_campus_bikes.cpp
        1000/1088_confusing_number_2.cpp
        1000/1143_longest_common_subsequence.cpp
        1000/1192_critical_connections_in_a_network.cpp
        1000/1306_jump_game_iii.cpp
        1000/1315_sum_of_even_grandparents.cpp
        1000/1335_minimum_difficulty_of_job_schedule.cpp
        1000/1405_longest_happy_string.cpp
        1000/1462_course_schedule_iv.cpp
        1000/1584_min_cost_to_connect_all_edges.cpp
        1000/1669_merge_inbetween_linked_lists.cpp

        misc/min_cost_to_repair_edges.cpp
        misc/five_star_sellers.cpp
        )

# Integrate Catch2 Testing Lib
find_package(Catch2 REQUIRED)
include(Catch)

# Add Support for #fmt
find_package(fmt)

# Add Utils
add_library(utils utils.cpp Tree.cpp)
target_link_libraries(utils fmt::fmt)
# Add Union Find
add_library(union_find UnionFind.cpp)
# Add Tarjan Solver
add_library(tarjan_solver TarjanSolver.cpp)

# Create Executables
foreach (SRC ${SRCS})
    get_filename_component(BIN ${SRC} NAME_WE) # Grab Filename w/o path and extension
    add_executable(${BIN} ${SRC} main.cpp) # Catch main should be its own file to avoid recompilation
    target_link_libraries(${BIN} PRIVATE Catch2::Catch2 fmt::fmt utils)
    catch_discover_tests(${BIN})
endforeach ()
