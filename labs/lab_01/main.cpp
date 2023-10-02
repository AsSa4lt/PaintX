#include <iostream>
#include <vector>
#include <span>

void print_all_subsets(std::vector<int>& prefix, std::span<int> set, bool rev) {
    if (set.empty()) {
        if(rev){
            for(auto it = prefix.rbegin(); it != prefix.rend(); ++it){
                std::cout << *it << " ";
            }
        }else {
            for (auto &&x: prefix) {
                std::cout << x << " ";
            }
        }
        std::cout << std::endl;
        return;
    }

    int head = set.front();

    // Exclude first
    print_all_subsets(prefix, std::span<int>(set.begin() + 1, set.end()), rev);

    // Include first
    prefix.push_back(head);
    print_all_subsets(prefix, std::span<int>(set.begin() + 1, set.end()), rev);

    // Remove the last element to backtrack and generate other subsets
    prefix.pop_back();
}

int main(int argc, char** argv) {
    bool rev = false;
    if(argc == 1 && argv[0] == "--reverse"){
        rev = true;
    }

    std::vector<int> input;
    int val;
    while (std::cin >> val) {
        input.push_back(val);
    }
    std::vector<int> s;
    print_all_subsets(s, input, rev);

    return 0;
}
