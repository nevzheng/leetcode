add_executable(tests
        test_295_find_median_from_data_stream.cpp

        main.cpp
        )

target_link_libraries(tests PRIVATE Catch2::Catch2)
target_link_libraries(tests PRIVATE solutions)
