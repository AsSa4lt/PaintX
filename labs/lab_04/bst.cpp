//
// Created by Rostyslav on 23.10.2023.
//

#include "bst.h"

void Bst::insert(std::string_view key) {
    auto p_node = std::make_unique<Node>(Node{std::string(key), nullptr, nullptr});
    if (_tree == nullptr) {
        // This calls move assignment operator
        // Deallocates the memory the prvious tree pointed to
        // Moves the ownership of the p_node
        _tree = move(p_node);
    }
    else {
        // Find the node to where we shall attach this new node
        auto [p_par, p_target, _] = find_node(nullptr, _tree.get(), p_node->data);

        auto cmp_res = p_node->data <=> p_par->data;
        // To the left
        if (cmp_res == std::strong_ordering::less) {
            p_par->p_left = move(p_node);
        }
            // To the right
        else {
            p_par->p_right = move(p_node);
        }
    }
}

Bst::FindNodeRes Bst::find_node(Node* p_par, Node* p_node, std::string_view target) const{
    if (p_node == nullptr) {
        return std::tuple(nullptr, nullptr, std::nullopt);
    }

    // Three-way comparison operator
    // (!)
    auto cmp_res = target <=> p_node->data;

    // Should search in left subtree
    if (cmp_res == std::strong_ordering::less) {
        // If the left child exists
        if (p_node->p_left != nullptr) {
            return  find_node(p_node, p_node->p_left.get(), target);
        }
            // Else, the item is not present
        else {
            return std::tuple(p_node, nullptr, std::nullopt);
        }
    }
        // If this it the element
    else if (cmp_res == std::strong_ordering::equivalent) {
        std::optional<ChildType> type = std::nullopt;
        if (p_par != nullptr) {
            if (p_par->p_left.get() == p_node) type = std::optional(ChildType::Left);
            else if (p_par->p_right.get() == p_node) type = std::optional(ChildType::Right);
        }
        return std::tuple(p_par, p_node, type);
    }
        // If should search in the right subtree
    else {
        // If the right child exists
        if (p_node->p_right != nullptr) {
            return  find_node(p_node, p_node->p_right.get(), target);
        }
            // Else, the item is not present
        else {
            return std::tuple(p_node, nullptr, std::nullopt);
        }
    }
}
Bst::FindMin Bst:: find_min(Node* p_par, Node* p_node){
    if (!p_node) return std::pair(p_par, nullptr);

    if (p_node->p_left)
        return find_min(p_node, p_node->p_left.get());
    else
        return std::pair(p_par, p_node);
}

std::optional<std::string> Bst::erase(std::string_view key) {
    auto [p_d_par, p_d, d_type] = find_node(nullptr, _tree.get(), key);

    // Nothing to delete
    if (p_d == nullptr) return std::nullopt;

    // copy assignment string operator==(const string& other)
    // (!) Be wary what heppens here with the move
    // the `p_d->data` was robbed and shall not be used
    std::string res = move(p_d->data);

    // Case 3: Two children
    if (p_d->p_left && p_d->p_right) {

        auto [p_s_par, p_s] = find_min(p_d, p_d->p_right.get());

        // Swap d <-> s
        // (!) must be beofre, nodes get dellocated
        // (!) we're swapping the robbed string, it is OK, we're not using it
        swap(p_d->data, p_s->data);

        // Is S my child?
        if (p_s_par == p_d) {
            // p_s gets deallocated here
            p_s_par->p_right = move(p_s->p_right);
        }
            // No, it is deeper
        else {
            // p_s gets deallocated here
            p_s_par->p_left = move(p_s->p_right);
        }
        // The deleted nodes are deallocated here since their unique_ptr were put out
        // by the move assignment operator

    }
        // Case 1: A leaf node && Case 2: One child
    else {
        // Get the child
        // We snatched the ownership from the node to be deleted
        std::unique_ptr<Node> p_s = (p_d->p_left ? move(p_d->p_left) : move(p_d->p_right));

        if (d_type == ChildType::Left) p_d_par->p_left = move(p_s);
        else if (d_type == ChildType::Right) p_d_par->p_right = move(p_s);
            // d_type == nullopt if root
        else _tree = move(p_s);
        // The deleted nodes are deallocated here since their unique_ptr were put out
        // by the move assignment operator
    }

    return res;
}

bool Bst::contains(std::string_view key) const {
    auto [_parent, _target, _type] = Bst::find_node(nullptr, _tree.get(), key);
    if(_target == nullptr) return  true;
    else return false;
}

std::vector<std::string> Bst::keys() const {
    auto nodes = Bst::get_sorted_nodes(_tree.get());
    std::vector<std::string> res;
    for(auto&& x: res)
        res.push_back(x);
    return res;
}
Bst::SortNodes Bst::get_sorted_nodes(const Node* p_node) const{
    std::vector<const Node*> res;

    if (!p_node) return res;

    auto a = get_sorted_nodes(p_node->p_left.get());
    res.insert(res.end(), a.begin(), a.end());

    res.push_back(p_node);
    auto b = get_sorted_nodes(p_node->p_right.get());
    res.insert(res.end(), b.begin(), b.end());
    return res;
}