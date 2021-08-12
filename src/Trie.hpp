//
// Created by Nevin Zheng on 8/12/21.
//

#pragma once

#include <memory>
#include <string>
#include <vector>

namespace trie {
struct Node {
  const size_t kAsciiLowerCaseCount{26};
  bool is_word_{false};
  std::vector<std::unique_ptr<Node>> children_{kAsciiLowerCaseCount};
  [[nodiscard]] bool isWord() const;
  /**
   * Return a non owning raw pointer to a child node.
   * @param c
   * @return A pointer to the child at c. Maybe null if the child does not exist
   */
  Node* get_child(char c);
  void setWord();

  /**
   * Return a valid ptr a child with value c, will construct a new Node
   * if it does not exist
   * @param c
   * @return
   */
  Node* make_child(char c);
};

class Trie {
 public:
  std::unique_ptr<Node> root_{new Node()};
  Trie() = default;
  /**
   * Insert a word into the trie
   * @param word
   */
  void insert(const std::string& word) const;
  [[nodiscard]] Node* get_root() const;

  static void find_words(Node* root, std::string& prefix,
                         std::vector<std::string>& words);
};
}  // namespace trie