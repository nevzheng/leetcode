set(SRCS
        814_binary_tree_pruning.cpp
        819_most_common_word.cpp
        827_making_a_large_island.cpp
        837_new_21_game.cpp
        838_push_dominoes.cpp
        841_keys_and_rooms.cpp
        877_stone_game.cpp
        886_possible_bipartition.cpp
        895_max_freq_stack.cpp
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
