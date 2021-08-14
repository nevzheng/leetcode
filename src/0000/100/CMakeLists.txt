set(SRCS
        105_construct_binary_tree_from_preorder_and_inorder_traversal.cpp
        108_convert_sorted_array_to_binary_search_tree.cpp
        110_balanced_binary_tree.cpp
        114_flatten_binary_tree_to_linked_list.cpp
        116_populating_next_right_pointers_in_each_node_1.cpp
        117_populating_next_right_pointers_in_each_node_2.cpp
        124_binary_tree_max_path_value.cpp
        126_word_ladder2.cpp
        127_word_ladder.cpp
        133_clone_graph.cpp
        138_copy_list_with_random_pointer.cpp
        139_word_break.cpp
        140_word_break_2.cpp
        144_preorder_traversal.cpp
        145_binary_tree_postorder_traversal.cpp
        146_lru_cache.cpp
        162_find_peak_element.cpp
        167_two_sum_2.cpp
        174_dungeon_game.cpp
        198_house_robber.cpp
        199_binary_tree_right_side_view.cpp
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
