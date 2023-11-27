#include <iostream>
#include <vector>
// ---
#include <algorithm>
#include <random>

#include "db.hpp"

using namespace mff;
using GenType = std::mt19937;
constexpr size_t PRICE_MIN = 100;
constexpr size_t PRICE_MAX = 500;

constexpr size_t NAME_MIN = 5;
constexpr size_t NAME_MAXX = 10;

constexpr size_t AREA_MIN = 20;
constexpr size_t AREA_MAX = 200;
constexpr size_t ROOMS_MIN = 1;
constexpr size_t ROOMS_MAX = 10;

constexpr float BR_MIN = 100;
constexpr float BR_MAX = 500;
constexpr const char LETTERS[] = "abcd";

/*! A number of random records to generate. */
constexpr size_t NUM_RECORDS = 100;
constexpr size_t SEED = 42;

/*! Prints the provided iterable object */
template <typename Cont>
void print(Cont xs) {
    for (auto&& x : xs) std::cout << x << " ";
    std::cout << std::endl;
}
std::string gen_name(GenType& gen) {
    std::uniform_int_distribution<size_t> dist_len(NAME_MIN, NAME_MAXX);
    std::uniform_int_distribution<size_t> dist_char(0, sizeof(LETTERS) - 1);
    auto len = dist_len(gen);
    std::string str(len, '\0');

    std::generate(str.begin(), str.end(), [&gen, &dist_char]() -> char {
        return LETTERS[dist_char(gen)];
    });

    return str;
}

size_t gen_area(GenType& gen) {
    std::uniform_int_distribution<size_t> dist(AREA_MIN, AREA_MAX);
    return dist(gen);
}

int gen_nr_rooms(GenType& gen) {
    std::uniform_int_distribution<size_t> dist(ROOMS_MIN, ROOMS_MAX);
    return dist(gen);
}

float gen_brightness(GenType& gen) {
    std::uniform_real_distribution<float> dist(BR_MIN, BR_MAX);
    return dist(gen);
}

int gen_price(GenType& gen) {
    std::uniform_int_distribution<size_t> dist(PRICE_MAX, PRICE_MIN);
    return dist(gen);
}

Ec get_ec(GenType& gen) {
    std::uniform_int_distribution<int> dist(0, 5); // 0 to 5 for Ec::A to Ec::F
    return static_cast<Ec>(dist(gen));
}




bool get_garage(GenType& gen) {
    std::discrete_distribution<unsigned short> d({1,9});
    auto res = d(gen);
    return  static_cast<bool>(res);
}

int main(int argc, char** argv) {
    Db db;
    GenType gen(SEED); // Initialize random number generator


    for(size_t i = 0; i < NUM_RECORDS; ++i) {
        db.insert(gen_name(gen), gen_price(gen), gen_area(gen), gen_nr_rooms(gen), gen_brightness(gen), get_ec(gen), get_garage(gen));
    }

    db.insert("House0", 100000, 30, 4, 0.8f, Ec::A, true);
    db.insert("House1", 300000, 50, 4, 0.8f, Ec::A, true);
    db.insert("House2", 450000, 200, 6, 0.7f, Ec::B, false);

    auto results = db.find({ 300000, 500000 }, { 20, 100 }, { 2, 5 }, { 0.2f, 1.0f }, { Ec::A, Ec::C }, true, 10);
    print(results);

    return 0;
}
