#pragma once
#include "std.hpp"

template <typename Int>
vector<int64_t> make_cumsum(const vector<Int>& v) {
    vector<int64_t> cumsum(v.size()+1);
    for (size_t i = 1; i < cumsum.size(); ++i) {
        cumsum[i] = cumsum[i-1] + v[i-1];
    }
    return cumsum;
}

// [first, last) の和を返す
inline int64_t sum_of(const vector<int64_t>& cumsum, int first, int last) noexcept {
    return cumsum[last] - cumsum[first];
}
