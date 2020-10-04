#pragma once
#include "std.hpp"

struct UnionFind {
    explicit UnionFind(int n): data(n, -1) {}
    bool merge(int x, int y) noexcept {
        x = leader(x);
        y = leader(y);
        if (x != y) {
            if (data[y] < data[x])
                swap(x, y);
            data[x] += data[y];
            data[y] = x;
        }
        return x != y;
    }
    bool same(int x, int y) noexcept {
        return leader(x) == leader(y);
    }
    int leader(int x) noexcept {
        return data[x] < 0 ? x : data[x] = leader(data[x]);
    }
    int size(int x) noexcept {
        return -data[leader(x)];
    }
private:
    vector<int> data;
};
