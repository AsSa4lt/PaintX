//
// Created by Rostyslav on 23.10.2023.
//
#ifndef BST_H_
#define BST_H_
#include "vector"
#include "string"

class Bst {
public:
    void insert(std::string_view key);
    std::optional<std::string> erase(std::string_view key);
    bool contains(std::string_view key) const;
    std::vector<std::string> keys() const;
private:
    enum class ChildType {
        Left,
        Right,
    };

    struct Node {
        std::string data;
        std::unique_ptr<Node> p_left;
        std:: unique_ptr<Node> p_right;
    };

    using FindNodeRes = std::tuple<Node*, Node*, std::optional<ChildType>>;
    using FindMin = std::pair<Node*, Node*>;
    using SortNodes = std::vector<const Node*>;
    FindNodeRes find_node(Node* p_par, Node* p_node, std::string_view target) const;
    std::pair<Node*, Node*> find_min(Node* p_par, Node* p_node);
    std::unique_ptr<Node> _tree;
    std::vector<const Node*> get_sorted_nodes(const Node* p_node) const;

};


#endif //BST_H_
