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
    string data;
    unique_ptr<Node> p_left;
    unique_ptr<Node> p_right;
};

/*!
 * Returns (ptr to parent of (potential) target, ptr to target, optional<ChildType>).
 */
tuple<Node*, Node*, optional<ChildType>> find_node(Node* p_par, Node* p_node, string target){

    if (p_node == nullptr) {
        return tuple(nullptr, nullptr, nullopt);
    }

    auto cmp_res = target <=> p_node->data;

    // Should search in left subtree
    if (cmp_res < 0) {
        // If the left child exists
        if (p_node->p_left != nullptr) {
            return find_node(p_node, p_node->p_left.get(), target);
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
            if (p_par->p_left.get() == p_node) type = optional(ChildType::Left);
            else if (p_par->p_right.get() == p_node) type = optional(ChildType::Right);
        }
        return tuple(p_par, move(p_node), type);
    }
        // If we should search in the right subtree
    else {
        // If the right child exists
        if (p_node->p_right != nullptr) {
            return  find_node(p_node, p_node->p_right.get(), target);
        }
            // Else, the item is not present
        else {
            return tuple(move(p_node), nullptr, nullopt);
        }
    }
}

/*!
 * Returns a sorted list of all nodes in the tree.
 */
vector<Node*> get_sorted_nodes(Node* p_node) {
    vector<Node*> res;

    if (!p_node) return res;

    auto a = get_sorted_nodes(p_node->p_left.get());
    res.insert(res.end(), a.begin(), a.end());

    res.push_back(p_node);

    auto b = get_sorted_nodes(p_node->p_right.get());
    res.insert(res.end(), b.begin(), b.end());

    return res;
}


/*!
 * Finds the node with the minimal value in the provided subtree.
 */
pair<Node*, Node*> find_min(Node* p_par, Node* p_node) {
    if (!p_node) return pair(p_par, nullptr);

    if (p_node->p_left)
        return find_min(p_node, p_node->p_left.get());
    else
        return pair(p_par, p_node);
}

/*!
 * Prints the tree as a sorted list.
 */
void print_tree(const unique_ptr<Node>& p_node) {
    auto nodes = get_sorted_nodes(p_node.get());

    cout << "--- TREE: ---" << endl;
    for (auto&& x : nodes)
        cout << x->data << " ";
    cout << endl;
    cout << "-------------" << endl;
}

/*!
 * Inserts the provided node into the provided BST.
 */
void insert_node(unique_ptr<Node>& p_tree, unique_ptr<Node>& p_node) {
    if (p_tree == nullptr) {
        p_tree = move(p_node);
    }
    else {
        // Find the node to where we shall attach this new node
        auto [p_par, p_target, _] = find_node(nullptr, p_tree.get(), p_node->data);

        auto cmp_res = p_node->data <=> p_par->data;
        // To the left
        if (cmp_res < 0) {
            p_par->p_left = move(p_node);
        }
            // To the right
        else {
            p_par->p_right = move(p_node);
        }
    }
}

/**
 * Deletes the node with value val from the tree and returns its values (it must be deallocated!).
 *
 * REMARKS:
 * Please mind the reference type of p_tree think about why it is there (hint: try to think
 * about cases where we're deleting the root node and where is the "main" pointer representing
 * the whole tree).
 */
unique_ptr<Node> find_min_node(unique_ptr<Node> node) {
    while (node->p_left != nullptr) {
        node = move(node->p_left);
    }
    return node;
}


string delete_node(unique_ptr<Node>& p_tree, const string val) {
    auto [p_d_par, p_d, d_type] = find_node(nullptr, p_tree.get(), val);    // Handle the case where the node to be deleted is the root

    if(p_d == nullptr) return nullptr;
    string res = p_d->data;

// Case 3: Two children
    if (p_d->p_left && p_d->p_right){
        auto [p_s_par, p_s] = find_min(p_d, p_d->p_right.get());
        // Swap d <-> s
        swap(p_d->data, p_s->data);
        // Is 5 my child?
        if (p_s_par == p_d) {
            p_s_par->p_right = move(p_s->p_right);
        }
            // No, it is deeper
        else {
            p_s_par->p_left = move(p_s->p_right);
        }
    }
        // Case 1: A leaf Node
    else if(!p_d->p_left && !p_d->p_right){
        // if not deleting root
        if(p_d_par != nullptr){
            if(d_type == ChildType::Left) p_d_par->p_left = nullptr;
            else p_d_par->p_right = nullptr;
        }else{
            p_tree = nullptr;
        }
    }
        // Case 2: One Child
    else {
        unique_ptr<Node> p_s = (p_d->p_left ? move(p_d->p_left) : move(p_d->p_right));

        // If not deleting root
        if(p_d_par != nullptr){
            if(d_type == ChildType::Left) p_d_par->p_left = move(p_s);
            else p_d_par->p_right = move(p_s);
        }else{
            p_tree = move(p_s);
        }
    }
    return res;
}


/*!
 * Initializes and allocates a new node with the provided value.
 */
unique_ptr<Node> construct_node(const string& value) {
    return make_unique<Node>(Node{value, nullptr, nullptr});
}


int main()
{
    // This represents the whole tree, its root
    unique_ptr<Node> p_tree = nullptr;

    //
    // Building the tree
    //
    string line;
    while (cin >> line) {
        // Strcmp results:
        // <0 => Left is less than R
        // == 0 => L & R are equal
        // >0 => Left is greater than R
        if (line == "=end=") break;

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
        string deleted = delete_node(p_tree, line);
        if (!deleted.empty()) {
            cout << "D: " << deleted << endl;
            // We must not forget to delete
            print_tree(p_tree);
        }
    }
    print_tree(p_tree);
}