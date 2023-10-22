#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include <algorithm>

using namespace std;

enum class ChildType {
    Left,
    Right,
};

struct Node {
    char* data;
    Node* p_left;
    Node* p_right;
};

/*!
 * Returns (ptr to parent of (potential) target, ptr to target, optional<ChildType>).
 */
tuple<Node*, Node*, optional<ChildType>> find_node(Node* p_par, Node* p_node, const char* target) {

    if (p_node == nullptr) {
        return tuple(nullptr, nullptr, nullopt);
    }

    auto cmp_res = strcmp(target, p_node->data);

    // Should search in left subtree
    if (cmp_res < 0) {
        // If the left child exists
        if (p_node->p_left != nullptr) {
            return  find_node(p_node, p_node->p_left, target);
        }
        // Else, the item is not present
        else {
            return tuple(p_node, nullptr, nullopt);
        }
    }
    // If this it the element
    else if (cmp_res == 0) {
        optional<ChildType> type = nullopt;
        if (p_par != nullptr) {
            if (p_par->p_left == p_node) type = optional(ChildType::Left);
            else if (p_par->p_right == p_node) type = optional(ChildType::Right);
        }
        return tuple(p_par, p_node, type);
    }
    // If should search in the right subtree
    else {
        // If the right child exists
        if (p_node->p_right != nullptr) {
            return  find_node(p_node, p_node->p_right, target);
        }
        // Else, the item is not present
        else {
            return tuple(p_node, nullptr, nullopt);
        }
    }
}

/*!
 * Returns a sorted list of all nodes in the tree.
 */
vector<const Node*> get_sorted_nodes(const Node* p_node) {
    vector<const Node*> res;

    if (!p_node) return res;

    auto a = get_sorted_nodes(p_node->p_left);
    res.insert(res.end(), a.begin(), a.end());

    res.push_back(p_node);
    auto b = get_sorted_nodes(p_node->p_right);
    res.insert(res.end(), b.begin(), b.end());
    return res;
}

/*!
 * Finds the node with the minimal value in the provided subtree.
 */
pair<Node*, Node*> find_min(Node* p_par, Node* p_node) {
    if (!p_node) return pair(p_par, nullptr);

    if (p_node->p_left)
        return find_min(p_node, p_node->p_left);
    else
        return pair(p_par, p_node);
}

/*!
 * Prints the tree as a sorted list.
 */
void print_tree(const Node* p_node) {
    auto nodes = get_sorted_nodes(p_node);

    cout << "--- TREE: ---" << endl;
    for (auto&& x : nodes)
        cout << x->data << " ";
    cout << endl;
    cout << "-------------" << endl;
}

/*!
 * Inserts the provided node into the provided BST.
 */
void insert_node(Node*& p_tree, Node* p_node) {
    if (p_tree == nullptr) {
        p_tree = p_node;
    }
    else {
        // Find the node to where we shall attach this new node
        auto [p_par, p_target, _] = find_node(nullptr, p_tree, p_node->data);

        auto cmp_res = strcmp(p_node->data, p_par->data);
        // To the left
        if (cmp_res < 0) {
            p_par->p_left = p_node;
        }
        // To the right
        else {
            p_par->p_right = p_node;
        }
    }
}

/**
 * Deletes the node with value `val` from the tree and returns its values (it must be deallocated!).
 *
 * REMARKS:
 * Please mind the reference type of `p_tree` think about why it is there (hint: try to think
 * about cases where we're deleting the root node and where is the "main" pointer representing
 * the whole tree).
 */
Node* find_min_node(Node* node) {
    while (node->p_left != nullptr) {
        node = node->p_left;
    }
    return node;
}


char* delete_node(Node*& p_tree, const char* val) {

    // Start by searching for the node
    auto [p_par, p_current, type] = find_node(nullptr, p_tree, val);

    // If the node isn't found, just return null
    if (p_current == nullptr) {
        return nullptr;
    }

    // Save a copy of the node's data to return at the end
    char* data_to_return = p_current->data;

    // If the node has both children
    if (p_current->p_left && p_current->p_right) {

        // Find the successor
        auto [p_s_par, p_successor] = find_min(p_current, p_current->p_right);

        // If the successor is the direct child of the current node
        if (p_s_par == p_current) {
            p_s_par->p_right = p_successor->p_right;
        }
            // If the successor is deeper in the tree
        else {
            p_s_par->p_left = p_successor->p_right;
        }

        // Swap the data of the current node and the successor
        swap(p_current->data, p_successor->data);

        // Update the pointer to delete the successor
        p_current = p_successor;
    }
        // If the node has one or no child
    else {
        Node* p_child = (p_current->p_left) ? p_current->p_left : p_current->p_right;

        // Check if the current node is a left or right child of its parent
        if (type == ChildType::Left) {
            p_par->p_left = p_child;
        } else if (type == ChildType::Right) {
            p_par->p_right = p_child;
        }
            // If the node is the root
        else {
            p_tree = p_child;
        }
    }

    // Delete the node
    delete p_current;

    // Return the saved data
    return data_to_return;
}







/*!
 * Initializes and allocates a new node with the provided value.
 */
Node* construct_node(const char* value) {
    // Allocate one extra space for '\n'
    auto word = new char[strlen(value) + 1];

    // Copy to the allocated memory (it includes the '\0')
    strcpy(word, value);

    // Here I am using "aggregate initialization" where I can initialize certain types (usable for structs like ours)
    // https://en.cppreference.com/w/cpp/language/aggregate_initialization
    return new Node{ word, nullptr, nullptr };
}

int main()
{
    // This represents the whole tree, its root
    Node* p_tree = nullptr;

    //
    // Building the tree
    //
    char line[256];
    while (cin >> line) {
        // Strcmp results:
        // <0 => Left is less than R
        // == 0 => L & R are equal
        // >0 => Left is greater than R
        if (strcmp(line, "=end=") == 0) break;

        auto p_new_node = construct_node(line);
        insert_node(p_tree, p_new_node);
    }

    print_tree(p_tree);

    //
    // Listening for queries
    //
    cout << "Listening for queries:" << endl;

    // Hit CTRL+Z (Win), CTRL+D(Linux) in the terminal to send EOF and end this loop
    while (cin >> line) {
        char* deleted = delete_node(p_tree, line);
        if (deleted) {
            cout << "D: " << deleted << endl;
            // We must not forget to delete
            delete deleted;
            print_tree(p_tree);
        }
    }
    print_tree(p_tree);
}
