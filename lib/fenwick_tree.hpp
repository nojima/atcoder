#pragma once
#include "std.hpp"

template <typename Int>
struct FenwickTree {
    vector<Int> data;
    explicit FenwickTree(int n): data(n, 0) {}
    void add(int i, Int x) {
        for (; i < (int)data.size(); i |= i+1)
            data[i] += x;
    }
    Int sum(int i) const {
        Int s = 0;
        for (; i >= 0; i = (i & (i+1)) - 1)
            s += data[i];
        return s;
    }
    Int sum(int a, int b) const { // inclusive
        return (a == 0) ? sum(b) : sum(b) - sum(a-1);
    }
};
