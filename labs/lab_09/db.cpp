//
// Created by Rostyslav on 27.11.2023.
//


#include "db.hpp"
// ---

using namespace mff;

void Db::insert(const std::string& name, size_t price, size_t area, size_t nr_rooms, float bf, Ec ec, bool garage) {
    auto prop = std::make_unique<Property>(Property{ name, price, area, nr_rooms, bf, ec, garage });
    _props.emplace_back(std::move(prop));
}

std::vector<const Property*> Db::find(I<size_t> price, I<size_t> area, I<size_t> rooms, I<float> brightness, I<Ec> ec,
                                      bool garage, size_t max_res) const {
    std::vector<const Property*> res;

    for (const auto& prop : _props) {
        if (prop->price >= price.first && prop->price <= price.second &&
            prop->area >= area.first && prop->area <= area.second &&
            prop->number_of_rooms >= rooms.first && prop->number_of_rooms <= rooms.second &&
            prop->brightness_factor >= brightness.first && prop->brightness_factor <= brightness.second &&
            static_cast<int>(prop->energy_class) >= static_cast<int>(ec.first) &&
            static_cast<int>(prop->energy_class) <= static_cast<int>(ec.second) &&
            prop->garage == garage) {

            res.push_back(prop.get());
            if (res.size() >= max_res) {
                break;
            }
            }
    }
    return res;
}
