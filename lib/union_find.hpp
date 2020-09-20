#pragma once
#include "std.hpp"

struct UnionFind {
    vector<int> data;
    explicit UnionFind(int size): data(size, -1) {}
    bool merge(int x, int y) noexcept {
        x = root(x);
        y = root(y);
        if (x != y) {
            if (data[y] < data[x])
                swap(x, y);
            data[x] += data[y];
            data[y] = x;
        }
        return x != y;
    }
    bool find(int x, int y) noexcept {
        return root(x) == root(y);
    }
    int root(int x) noexcept {
        return data[x] < 0 ? x : data[x] = root(data[x]);
    }
    int size(int x) noexcept {
        return -data[root(x)];
    }
};
