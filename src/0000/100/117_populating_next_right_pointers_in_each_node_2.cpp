//// 117_populating_next_right_pointers_in_each_node_2
//// Nevin Zheng
//// 7/18/21
//
//#include <queue>
//
//#include <catch2/catch.hpp>
//#include <fmt/format.h>
//
//using namespace std;
//
//// Definition for a Node.
//class Node {
//public:
//    int val;
//    Node *left;
//    Node *right;
//    Node *next;
//
//    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}
//
//    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}
//
//    Node(int _val, Node *_left, Node *_right, Node *_next)
//        : val(_val), left(_left), right(_right), next(_next) {}
//};
//
//Node *connect(Node *root) {
//    if (!root) return nullptr;
//    std::queue<Node *> bfs{{root}};
//    while (!bfs.empty()) {
//        auto k = bfs.size();
//        for (auto i = 0; i < k; i++) {
//            auto curr = bfs.front();
//            bfs.pop();
//            // Adjust the pointers, but skip the Last element in the queue
//            if (i < k - 1) curr->next = bfs.front();
//            // Push the Next Level
//            if (curr->left) bfs.push(curr->left);
//            if (curr->right) bfs.push(curr->right);
//        }
//    }
//    return root;
//}
////
////
////TEST_CASE("117ex1", "[117]") {
////    auto input = {};
////    auto expected = {};
////    REQUIRE(connect(input) == expected);
////}