set(SRCS
        200_number_of_islands.cpp
        205_isomorphic_strings.cpp
        207_course_schedule.cpp
        210_course_schedule_ii.cpp
        212_word_search_ii.cpp
        213_house_robber_2.cpp
        216_combination_sum_3.cpp
        221_maximal_square.cpp
        222_count_complete_tree_nodes.cpp
        223_rectangle_area.cpp
        236_lca_bt.cpp
        242_valid_anagram.cpp
        257_binary_tree_paths.cpp
        268_missing_number.cpp
        269_alien_dictionary.cpp
        295_find_median_from_data_stream.cpp
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
