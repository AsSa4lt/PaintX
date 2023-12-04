
#include <iostream>

/*! Prints the provided iterable object */
template <typename Cont>
void print(Cont xs) {
	for (auto&& x : xs) std::cout << x << " ";
	std::cout << std::endl;
}