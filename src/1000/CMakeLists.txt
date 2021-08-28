set(SRCS
        1008_construct_binary_search_tree_from_preorder_traversal.cpp
        1034_find_n_unique_integers_sum_up_to_zero.cpp
        1041_robot_bounded_in_circle.cpp
        1046_last_stone_weight.cpp
        1056_confusing_number.cpp
        1057_campus_bikes.cpp
        1088_confusing_number_2.cpp
        1143_longest_common_subsequence.cpp
        1192_critical_connections_in_a_network.cpp
        1235_maximum_profit_in_job_scheduling.cpp
        1268_search_suggestion_system.cpp
        1306_jump_game_iii.cpp
        1315_sum_of_even_grandparents.cpp
        1335_minimum_difficulty_of_job_schedule.cpp
        1339_maximum_product_bt.cpp
        1462_course_schedule_iv.cpp
        1448_count_good_nodes_in_bt.cpp
        1584_min_cost_to_connect_all_edges.cpp
        1669_merge_inbetween_linked_lists.cpp
        )
# Add Catch2 Definition
include(Catch)

# Create Executables
foreach (SRC ${SRCS})
    get_filename_component(BIN ${SRC} NAME_WE) # Grab Filename w/o path and extension
    add_executable(${BIN} ${SRC} ../main.cpp) # Catch main should be its own file to avoid recompilation
    target_link_libraries(${BIN} PRIVATE CONAN_PKG::catch2 CONAN_PKG::fmt utils trie union_find tarjan_solver)
    catch_discover_tests(${BIN})
endforeach ()
