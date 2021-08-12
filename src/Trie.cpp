// Trie.cpp
// Created by Nevin Zheng on 8/12/21.
//

//
// Created by Nevin Zheng on 8/12/21.
//

#include "Trie.hpp"

namespace trie {
Node* Node::get_child(char c) { return children_.at(c - 'a').get(); }

Node* Node::make_child(char c) {
  if (auto* cp = get_child(c); cp != nullptr) return cp;
  children_[c - 'a'] = std::make_unique<Node>();
  return get_child(c);
}

bool Node::isWord() const { return is_word_; }

void Node::setWord() { is_word_ = true; }

void Trie::insert(const std::string& word) const {
  auto* cur = root_.get();
  for (auto c : word) {
    cur = cur->make_child(c);
  }
  cur->setWord();
}

Node* Trie::get_root() const { return root_.get(); }

void Trie::find_words(Node* root, std::string& prefix,
                      std::vector<std::string>& words) {
  if (words.size() == 3) return;
  if (root->isWord()) words.push_back(prefix);
  for (auto c = 'a'; c <= 'z'; ++c) {
    if (auto* p = root->get_child(c); p != nullptr) {
      prefix += c;
      find_words(p, prefix, words);
      prefix.pop_back();
    }
  }
}
}  // namespace trie
