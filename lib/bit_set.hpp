#pragma once
#include "std.hpp"

struct BitSet {
    uint32_t data;
    explicit BitSet(uint32_t data): data(data) {}
    inline bool operator[](int i) const noexcept { return (data >> i) & 1; }
    inline int size() const noexcept { return __builtin_popcount(data); }
};

template<class Func>
void foreach_power_set(int n, Func f) {
    for (uint32_t S = 0; S < (uint32_t)(1 << n); ++S) {
        f(BitSet(S));
    }
}
