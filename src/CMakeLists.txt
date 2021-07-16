add_executable(tests
        1_two_sum.cpp
        22_generate_parentheses.cpp
        114_flatten_binary_tree_to_linked_list.cpp
        162_find_peak_element.cpp
        205_isomorphic_strings.cpp
        207_course_schedule.cpp
        210_course_schedule_ii.cpp
        295_find_median_from_data_stream.cpp
        347_top_k_frequent_elements.cpp
        611_valid_triangle_number.cpp
        787_cheapest_flights_within_k_stops.cpp
        814_binary_tree_pruning.cpp
        886_possible_bipartition.cpp
        1462_course_schedule_iv.cpp
        1669_merge_inbetween_linked_lists.cpp

        main.cpp
        )

target_link_libraries(tests PRIVATE Catch2::Catch2)
