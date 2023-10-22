#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include <algorithm>
#include <memory>

using namespace std;

enum class ChildType {
    Left,
    Right,
};

struct Node {
    string data;
    unique_ptr<Node> p_left;
    unique_ptr<Node> p_right;
};

tuple<Node*, Node*, optional<ChildType>> find_node(Node* p_par, Node* p_node, const string& target) {
    if (!p_node) return {nullptr, nullptr, nullopt};

    if (target < p_node->data) {
        return p_node->p_left ? find_node(p_node, p_node->p_left.get(), target) : tuple(p_node, nullptr, nullopt);
    } else if (target == p_node->data) {
        optional<ChildType> type = nullopt;
        if (p_par) {
            if (p_par->p_left.get() == p_node) type = ChildType::Left;
            else if (p_par->p_right.get() == p_node) type = ChildType::Right;
        }
        return {p_par, p_node, type};
    } else {
        return p_node->p_right ? find_node(p_node, p_node->p_right.get(), target) : tuple(p_node, nullptr, nullopt);
    }
}

vector<const Node*> get_sorted_nodes(const Node* p_node) {
    vector<const Node*> res;
    if (!p_node) return res;

    auto a = get_sorted_nodes(p_node->p_left.get());
    res.insert(res.end(), a.begin(), a.end());

    res.push_back(p_node);
    auto b = get_sorted_nodes(p_node->p_right.get());
    res.insert(res.end(), b.begin(), b.end());
    return res;
}

pair<Node*, Node*> find_min(Node* p_par, Node* p_node) {
    if (!p_node) return {p_par, nullptr};

    return p_node->p_left ? find_min(p_node, p_node->p_left.get()) : pair(p_par, p_node);
}

void print_tree(const Node* p_node) {
    auto nodes = get_sorted_nodes(p_node);

    cout << "--- TREE: ---" << endl;
    for (const auto& x : nodes)
        cout << x->data << " ";
    cout << endl << "-------------" << endl;
}

void insert_node(unique_ptr<Node>& p_tree, unique_ptr<Node>& p_node) {
    if (!p_tree) {
        p_tree = move(p_node);
    } else {
        auto [p_par, _, a] = find_node(nullptr, p_tree.get(), p_node->data);

        if (p_node->data < p_par->data) {
            p_par->p_left = move(p_node);
        } else {
            p_par->p_right = move(p_node);
        }
    }
}

string delete_node(unique_ptr<Node>& p_tree, const string& val) {
    // Start by searching for the node
    auto [parent, current, type] = find_node(nullptr, p_tree.get(), val);

    // Node not found
    if (!current) {
        return "";
    }

    // Save the data of the node we're going to delete
    string deletedData = current->data;

    // Lambda to remove a node based on child type
    auto removeNode = [&]() {
        if (type == ChildType::Left) {
            parent->p_left.reset();
        } else if (type == ChildType::Right) {
            parent->p_right.reset();
        }
    };

    // Leaf node
    if (!current->p_left && !current->p_right) {
        removeNode();
    }
        // Node with only a right child
    else if (!current->p_left) {
        if (type == ChildType::Left) {
            parent->p_left = move(current->p_right);
        } else {
            parent->p_right = move(current->p_right);
        }
    }
        // Node with only a left child
    else if (!current->p_right) {
        if (type == ChildType::Left) {
            parent->p_left = move(current->p_left);
        } else {
            parent->p_right = move(current->p_left);
        }
    }
        // Node with both children
    else {
        // The successor is either the node's right child or the right child's leftmost child
        Node* successorParent = current;
        auto* successorNode = &(current->p_right);
        while ((*successorNode)->p_left) {
            successorParent = successorNode->get();
            successorNode = &((*successorNode)->p_left);
        }

        current->data = (*successorNode)->data;

        // If the successor has a right child, move it up to the successor's position
        if ((*successorNode)->p_right) {
            *successorNode = move((*successorNode)->p_right);
        } else {
            if (successorParent->p_left.get() == successorNode->get()) {
                successorParent->p_left.reset();
            } else {
                successorParent->p_right.reset();
            }
        }
    }

    return deletedData;
}



unique_ptr<Node> construct_node(const string& value) {
    return make_unique<Node>(Node{value, nullptr, nullptr});
}

int main() {
    unique_ptr<Node> p_tree;

    string line;
    while (cin >> line && line != "=end=") {
        auto p_new_node = construct_node(line);
        insert_node(p_tree, p_new_node);
    }

    print_tree(p_tree.get());

    cout << "Listening for queries:" << endl;
    while (cin >> line) {
        string deleted = delete_node(p_tree, line);
        if (!deleted.empty()) {
            cout << "D: " << deleted << endl;
            print_tree(p_tree.get());
        }
    }
    print_tree(p_tree.get());
}
