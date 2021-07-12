add_executable(tests
        205_isomorphic_strings.cpp
        295_find_median_from_data_stream.cpp

        main.cpp
        )

target_link_libraries(tests PRIVATE Catch2::Catch2)
