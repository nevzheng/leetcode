set(SRCS
        0000/000/1_two_sum.cpp
        0000/000/15_3_sum.cpp
        0000/000/17_letter_combinations_of_a_phone_number.cpp
        0000/000/18_4_sum.cpp
        0000/000/22_generate_parentheses.cpp
        0000/000/25_reverse_nodes_in_k_group.cpp
        0000/000/39_combination_sum.cpp
        0000/000/40_combination_sum.cpp
        0000/000/41_first_missing_positive.cpp
        0000/000/45_jump_game_2.cpp

        0000/100/114_flatten_binary_tree_to_linked_list.cpp
        0000/100/116_populating_next_right_pointers_in_each_node_1.cpp
        0000/100/117_populating_next_right_pointers_in_each_node_2.cpp
        0000/100/126_word_ladder2.cpp
        0000/100/127_word_ladder.cpp
        0000/100/133_clone_graph.cpp
        0000/100/138_copy_list_with_random_pointer.cpp
        0000/100/162_find_peak_element.cpp
        0000/100/167_two_sum_2.cpp
        0000/100/174_dungeon_game.cpp
        0000/100/198_house_robber.cpp

        0000/200/205_isomorphic_strings.cpp
        0000/200/207_course_schedule.cpp
        0000/200/210_course_schedule_ii.cpp
        0000/200/216_combination_sum_3.cpp
        0000/200/221_maximal_square.cpp
        0000/200/269_alien_dictionary.cpp
        0000/200/295_find_median_from_data_stream.cpp

        0000/300/347_top_k_frequent_elements.cpp
        0000/300/377_combination_sum_iv.cpp

        0000/400/416_partition_equal_subset_sum.cpp
        0000/400/427_concatenated_words.cpp

        0000/500/513_find_bottom_left_tree_value.cpp
        0000/500/543_diameter_of_binary_tree.cpp

        0000/600/611_valid_triangle_number.cpp
        0000/600/662_maximum_width_of_binary_tree.cpp

        0000/700/785_is_graph_bipartite.cpp
        0000/700/787_cheapest_flights_within_k_stops.cpp

        0000/800/814_binary_tree_pruning.cpp
        0000/800/838_push_dominoes.cpp
        0000/800/841_keys_and_rooms.cpp
        0000/800/886_possible_bipartition.cpp

        0000/900/915_partition_array_into_disjoint_intervals.cpp
        0000/900/927_three_equal_parts.cpp
        0000/900/987_vertical_order_traversal_of_a_binary_tree.cpp

        1000/1462_course_schedule_iv.cpp
        1000/1669_merge_inbetween_linked_lists.cpp
        )

# Integrate Catch2 Testing Lib
find_package(Catch2 REQUIRED)
include(Catch)

# Add Support for #fmt
find_package(fmt)

# Create Executables
foreach (SRC ${SRCS})
    get_filename_component(BIN ${SRC} NAME_WE) # Grab Filename w/o path and extension
    add_executable(${BIN} ${SRC} main.cpp utils.cpp) # Catch main should be its own file to avoid recompilation
    target_link_libraries(${BIN} PRIVATE Catch2::Catch2 fmt::fmt)
    catch_discover_tests(${BIN})
endforeach ()
