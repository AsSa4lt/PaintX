
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>
#include <string>
#include <optional>
#include <algorithm>
#include <tuple>
#include <cstring>

#include "bst.h"
int main()
{
    Bst tree;
    // This represents the whole tree, its root

    //
    // Building the tree
    //
    std::string line;
    while (std::cin >> line) {

        if (line == "=end=") break;
        tree.insert(line);
    }

    //print_tree(p_tree);

    //
    // Listening for queries
    //
    // cout << "Listening for queries:" << endl;

    // Hit CTRL+Z (Win), CTRL+D(Linux) in the terminal to send EOF and end this loop
    while (std::cin >> line) {
        std::optional<std::string> deleted = tree.erase(line);
        if (deleted) {
            std::cout << "D: " << deleted.value() << std::endl;
        }
    }
    //print_tree(p_tree);
}

