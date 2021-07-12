add_library(solutions
        205_isomorphic_strings.cpp
        295_find_median_from_data_stream.cpp
        )
target_link_libraries(solutions PRIVATE Catch2::Catch2)