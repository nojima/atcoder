#pragma once
#include "std.hpp"
#include <boost/iterator/iterator_adaptor.hpp>

struct BitSet {
    const uint32_t data;
    explicit BitSet(uint32_t data): data(data) {}
    inline bool operator[](int i) const noexcept {
        return (data >> i) & 1;
    }
    inline int size() const noexcept {
        return __builtin_popcount(data);
    }
    inline BitSet exclude(int i) const noexcept {
        assert((*this)[i]);
        return BitSet(data ^ (1 << i));
    }
};

// 集合 {0, 1, .., n-1} のすべての部分集合を列挙する。
template <class Func>
void foreach_subset(int n, Func f) {
    for (uint32_t S = 0; S < (uint32_t)(1 << n); ++S) {
        f(BitSet(S));
    }
}

// S のすべての部分集合(∅ と S 自身を含む)を列挙する。
template <class Func>
void foreach_subset_of(BitSet S, Func f) {
    uint32_t whole = S.data;
    uint32_t subset = 0;
    for (;;) {
        f(BitSet(subset));
        if (subset == whole) { return; }
        subset = (subset - whole) & whole;
    }
}

// 要素数が k であるような {0, 1, .., n-1} の部分集合をすべて列挙する。
template <class Func>
void foreach_subset_with_size(int n, int k, Func f) {
    // 蟻本 p144 より
    uint32_t subset = (1 << k) - 1;
    while (subset < (uint32_t)(1 << n)) {
        f(BitSet(subset));
        uint32_t x = subset & -subset; // 最下位の1
        uint32_t y = subset + x;       // 最下位の1が連続している区間を繰り上げたもの
        uint32_t z = subset & ~y;      // 最下位の1が連続している区間
        subset = ((z / x) >> 1) | y;
    }
}
