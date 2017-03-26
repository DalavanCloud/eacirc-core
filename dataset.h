#pragma once

#include "iterators.h"
#include "view.h"
#include <vector>

struct dataset {
    using storage = std::vector<std::uint8_t>;

    using pointer = storage::pointer;
    using const_pointer = storage::const_pointer;

    using iterator = step_iterator<view_iterator<typename storage::iterator>>;
    using const_iterator = step_iterator<view_iterator<typename storage::const_iterator>>;

    dataset()
        : _tvsize(0)
        , _data() {}

    dataset(unsigned tv_size, std::size_t n)
        : _tvsize(tv_size)
        , _data(tv_size * n) {}

    dataset(dataset&&) = default;
    dataset(dataset const&) = default;

    dataset& operator=(dataset&&) = default;
    dataset& operator=(dataset const&) = default;

    iterator begin() { return {{_data.begin(), _tvsize}, _tvsize}; }
    iterator end() { return {{_data.end(), _tvsize}, _tvsize}; }

    const_iterator begin() const { return {{_data.begin(), _tvsize}, _tvsize}; }
    const_iterator end() const { return {{_data.end(), _tvsize}, _tvsize}; }

    std::size_t tvsize() const { return _tvsize; }
    std::size_t size() const { return _data.size() / _tvsize; }

    pointer rawdata() { return _data.data(); }
    const_pointer rawdata() const { return _data.data(); }

    std::size_t rawsize() const { return _data.size(); }

private:
    unsigned _tvsize;
    storage _data;
};
