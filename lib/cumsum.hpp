#pragma once
#include "std.hpp"

template <typename Int>
vector<Int> make_cumsum(const vector<Int>& v) {
    vector<Int> cumsum(v.size()+1);
    for (size_t i = 1; i < cumsum.size(); ++i) {
        cumsum[i] = cumsum[i-1] + v[i-1];
    }
    return cumsum;
}

// [first, last) の和を返す
template <typename Int>
inline Int sum_of(const vector<Int>& cumsum, int first, int last) noexcept {
    return cumsum[last] - cumsum[first];
}
