#ifndef DB_H_
#define DB_H_

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace mff {

/*! Energy class   */
enum class Ec : unsigned short { A, B, C, D, E, F };

/*! Interval type */
template <typename T>
using I = std::pair<T, T>;

template <typename T>
bool operator==(const I<T>& a, const T& b) {
	return a.first <= b and b <= a.second;
}

template <typename T>
bool operator==(const T& b, const I<T>& a) {
	return a.first <= b and b <= a.second;
}

/*! Represents a property for sale. */
struct Property {
	std::string name;
	size_t price;
	size_t area;
	size_t number_of_rooms;
	float brightness_factor;
	Ec energy_class;
	bool garage;
};

/*! Result returned by the database queries. */
using QueryRes = std::vector<const Property*>;

class Db {
public:
	void insert(const std::string& name, size_t price, size_t area, size_t nr_rooms, float bf, Ec ec, bool garage);
	void rebuild_indices();
	QueryRes find_basic(I<size_t> price, I<size_t> area, I<size_t> rooms, I<float> brightness, I<Ec> ec, bool garage,
	                    size_t max_res) const;
	QueryRes find_ranges(I<size_t> price, I<size_t> area, I<size_t> rooms, I<float> brightness, I<Ec> ec, bool garage,
	                     size_t max_res) const;

private:
	std::vector<std::unique_ptr<Property>> _props;
	// ---
	std::vector<Property*> _price_idx;
	std::vector<Property*> _area_idx;
	std::vector<Property*> _room_idx;
	std::vector<Property*> _bf_idx;
	std::vector<Property*> _ec_idx;
	std::vector<Property*> _garage_idx;
};

};      // namespace mff
#endif  // DB_H_
