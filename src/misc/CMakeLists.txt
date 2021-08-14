set(SRCS
        five_star_sellers.cpp
        min_cost_to_repair_edges.cpp
        string_distance.cpp

        OA_movies_on_a_flight.cpp
        OA_10_max_of_min_altitude.cpp
        OA_11_min_cost_to_connect_ropes.cpp
        OA_12_treasure_island.cpp
        OA_13_favorite_genres.cpp
        OA_14_treasure_island_2.cpp
        OA_18_subtree_with_max_average.cpp
        OA_21_two_sum_unique_pairs.cpp
        OA_24_substr_of_size_k_with_k_distinct_char.cpp
        OA_30_optimal_utilization.cpp
        OA_shopping_options.cpp
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
