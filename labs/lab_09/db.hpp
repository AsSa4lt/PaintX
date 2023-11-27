#ifndef DB_H_
#define DB_H_

#include <utility>
#include <string>
#include <vector>
#include <memory>

namespace mff {

    /*! Energy class   */
    enum class Ec : unsigned char { A, B, C, D, E, F };

    /*! Interval type */
    template <typename T>
    using I = std::pair<T, T>;

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

        QueryRes find(I<size_t> price, I<size_t> area, I<size_t> rooms, I<float> brightness, I<Ec> ec, bool garage,
                      size_t max_res) const;

    private:
        std::vector<std::unique_ptr<Property>> _props;
    };

};      // namespace mff
#endif  // DB_H_
