#include <chrono>
#include <iostream>
#include <random>
#include <ranges>
#include <vector>
// ---
#include "db.h"
#include "utils.hpp"

using namespace mff;

//
// CONFIG
//

// PRNG type to use
using GenType = std::mt19937_64;

/*! A number of random records to generate. */
constexpr size_t NUM_RECORDS = 1000;
constexpr size_t NUM_QUERIES = 100000;
constexpr size_t SEED = 42;
// ---
constexpr size_t NAME_MIN = 5;
constexpr size_t NAME_MAX = 10;
constexpr size_t PRICE_MIN = 100000;
constexpr size_t PRICE_MAX = 500000;
constexpr size_t AREA_MIN = 20;
constexpr size_t AREA_MAX = 200;
constexpr size_t ROOMS_MIN = 1;
constexpr size_t ROOMS_MAX = 10;
constexpr float BR_MIN = 0.0f;
constexpr float BR_MAX = 1.0f;
constexpr const char LETTERS[] = "abcdefghijklmopqrstuvwxyz";

using Query = std::tuple<I<size_t>, I<size_t>, I<size_t>, I<float>, I<Ec>, bool>;

std::string gen_string(GenType& gen) {
	std::uniform_int_distribution<size_t> len_dist(NAME_MIN, NAME_MAX);
	std::uniform_int_distribution<size_t> char_dist(0, sizeof(LETTERS) - 2);

	size_t name_len = len_dist(gen);
	std::string result(name_len, '\0');

	std::generate(result.begin(), result.end(), [&gen, &char_dist]() { return LETTERS[char_dist(gen)]; });

	return result;
}

size_t gen_price(GenType& gen) {
	std::uniform_int_distribution<size_t> dist(PRICE_MIN, PRICE_MAX);
	return dist(gen);
}

size_t gen_area(GenType& gen) {
	std::uniform_int_distribution<size_t> dist(AREA_MIN, AREA_MAX);
	return dist(gen);
}

size_t gen_rooms(GenType& gen) {
	std::uniform_int_distribution<size_t> dist(ROOMS_MIN, ROOMS_MAX);
	return dist(gen);
}

float gen_brightness(GenType& gen) {
	std::uniform_real_distribution<float> dist(BR_MIN, BR_MAX);
	return dist(gen);
}

Ec gen_ec(GenType& gen) {
	std::discrete_distribution dist({ 1, 10, 5, 3, 2, 1 });
	return static_cast<Ec>(dist(gen));
}

bool gen_garage(GenType& gen) {
	// (!) We want to have 90% of samples set to `true`
	// !NOT! std::discrete_distribution dist(1, 9) -> ctor;
	std::discrete_distribution dist({ 1, 9 });
	return static_cast<bool>(dist(gen));
}

void gen_records(Db& db, size_t count, size_t seed) {
	// Create one generator
	GenType gen(seed);

	for (auto&& i : std::views::iota(0) | std::views::take(count)) {
		db.insert(gen_string(gen), gen_price(gen), gen_area(gen), gen_rooms(gen), gen_brightness(gen), gen_ec(gen),
		          gen_garage(gen));
	}
}

I<size_t> gen_price_i(GenType& gen) {
	std::uniform_int_distribution<size_t> dist(PRICE_MIN, PRICE_MAX);

	auto fst = dist(gen);
	auto snd = dist(gen);

	if (fst > snd) std::swap(fst, snd);

	return I<size_t>(fst, snd);
}

I<size_t> gen_area_i(GenType& gen) {
	std::uniform_int_distribution<size_t> dist(AREA_MIN, AREA_MAX);

	auto fst = dist(gen);
	auto snd = dist(gen);

	if (fst > snd) std::swap(fst, snd);

	return I<size_t>(fst, snd);
}

I<size_t> gen_rooms_i(GenType& gen) {
	std::uniform_int_distribution<size_t> dist(ROOMS_MIN, ROOMS_MAX);

	auto fst = dist(gen);
	auto snd = dist(gen);

	if (fst > snd) std::swap(fst, snd);

	return I<size_t>(fst, snd);
}

I<float> gen_brightness_i(GenType& gen) {
	std::uniform_real_distribution<float> dist(BR_MIN, BR_MAX);

	auto fst = dist(gen);
	auto snd = dist(gen);

	if (fst > snd) std::swap(fst, snd);

	return I<float>(fst, snd);
}

I<Ec> gen_ec_i(GenType& gen) {
	std::discrete_distribution dist({ 1, 10, 5, 3, 2, 1 });

	auto fst = dist(gen);
	auto snd = dist(gen);

	if (fst > snd) std::swap(fst, snd);

	return I<Ec>(static_cast<Ec>(fst), static_cast<Ec>(snd));
}

std::vector<Query> gen_queries(size_t count, size_t seed) {
	// Create one generator
	GenType gen(seed);
	std::vector<Query> res;

	for (auto&& i : std::views::iota(size_t(0), count)) {
		res.emplace_back(gen_price_i(gen), gen_area_i(gen), gen_rooms_i(gen), gen_brightness_i(gen), gen_ec_i(gen),
		                 gen_garage(gen));
	}

	return res;
}

int main(int argc, char** argv) {
	Db db;

	gen_records(db, NUM_RECORDS, SEED);

	auto queries = gen_queries(NUM_QUERIES, SEED);
	db.rebuild_indices();

	// auto res = db.find_indices(I<size_t>(100000, 110000), I<size_t>(100, 110), I<size_t>(5, 6), I<float>(0.57f,
	// 0.59f), I<Ec>(Ec::E, Ec::E), true, 10);

	std::vector<QueryRes> ress;
	ress.reserve(NUM_QUERIES);

	auto start = std::chrono::high_resolution_clock::now();
	for (const auto& [price, area, rooms, br, ec, gar] : queries) {
		ress.emplace_back(db.find_basic(price, area, rooms, br, ec, gar, 100));
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "basic: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << std::endl;

	std::vector<QueryRes> ress2;
	ress2.reserve(NUM_QUERIES);

	start = std::chrono::high_resolution_clock::now();
	for (const auto& [price, area, rooms, br, ec, gar] : queries) {
		ress2.emplace_back(db.find_ranges(price, area, rooms, br, ec, gar, 100));
	}
	end = std::chrono::high_resolution_clock::now();
	std::cout << "ranges: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << std::endl;

	return 0;
}
