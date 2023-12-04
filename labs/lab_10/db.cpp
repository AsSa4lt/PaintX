
#include "db.h"
// ---
#include <algorithm>
#include <iostream>
#include <ranges>

using namespace mff;

void Db::insert(const std::string& name, size_t price, size_t area, size_t nr_rooms, float bf, Ec ec, bool garage) {
	auto prop = std::make_unique<Property>(Property{ name, price, area, nr_rooms, bf, ec, garage });
	_props.emplace_back(std::move(prop));
}

void Db::rebuild_indices() {
	using namespace std::ranges;
	//Price
	_price_idx.resize(_props.size());
	copy(_props | std::views::transform([](auto const& x){ return x.get(); }), _price_idx.begin());
	sort(_price_idx, {}, [](const Property* p){return p->price;});

	// Area
	_area_idx.resize(_props.size());
	copy(_props | std::views::transform([](auto const& x){ return x.get(); }), _area_idx.begin());
	sort(_area_idx, {}, [](const Property* p){return p->area;});

	// Rooms
	_room_idx.resize(_props.size());
	copy(_props | std::views::transform([](auto const& x){ return x.get(); }), _room_idx.begin());
	sort(_room_idx, {}, [](const Property* p){return p->number_of_rooms;});

	// Brightness
	_bf_idx.resize(_props.size());
	copy(_props | std::views::transform([](auto const& x){ return x.get(); }), _bf_idx.begin());
	sort(_bf_idx, {}, [](const Property* p){return p->brightness_factor;});

	// EC
	_ec_idx.resize(_props.size());
	copy(_props | std::views::transform([](auto const& x){ return x.get(); }), _ec_idx.begin());
	sort(_ec_idx, {}, [](const Property* p){return p->energy_class;});

	// Garage
	_garage_idx.resize(_props.size());
	copy(_props | std::views::transform([](auto const& x){ return x.get(); }), _garage_idx.begin());
	sort(_garage_idx, {}, [](const Property* p){return p->garage;});

}

std::vector<const Property*> Db::find_basic(I<size_t> price, I<size_t> area, I<size_t> rooms, I<float> brightness,
                                            I<Ec> ec, bool garage, size_t max_res) const {
	std::vector<const Property*> res;

	for (const auto& prop : _props) {
		if (prop->price >= price.first && prop->price <= price.second && prop->area >= area.first &&
		    prop->area <= area.second && prop->number_of_rooms >= rooms.first &&
		    prop->number_of_rooms <= rooms.second && prop->brightness_factor >= brightness.first &&
		    prop->brightness_factor <= brightness.second &&
		    static_cast<int>(prop->energy_class) >= static_cast<int>(ec.first) &&
		    static_cast<int>(prop->energy_class) <= static_cast<int>(ec.second) && prop->garage == garage) {
			res.push_back(prop.get());
			if (res.size() >= max_res) {
				break;
			}
		}
	}
	return res;
}

QueryRes Db::find_ranges(I<size_t> price, I<size_t> area, I<size_t> rooms, I<float> brightness, I<Ec> ec, bool garage,
                         size_t max_res) const {
	using namespace std::views;
	QueryRes res;

	auto props_filtered = _props |  filter([price](const auto& p) {return price == p->price; }) |
									filter([area](const auto& p) {return area == p->area; }) |
									filter([rooms](const auto& p) {return rooms == p->rooms; }) |
									filter([brightness](const auto& p) {return brightness == p->brightness_factor; }) |
									filter([ec](const auto& p) {return ec == p->energy_class; }) |
									filter([garage](const auto& p) {return garage == p->garage; }) | take(max_res) |
									tranform([](const auto& p){return p.get();});

	std::ranges::copy(props_filtered, std::back_inserter(res));
	return res;
}
