#pragma once
#include "std.hpp"

template<class T>
struct PersistentArray {
    PersistentArray(int n, const T& init)
        : size(bit_ceil(n)), root(construct(init, 0, size)) {}

    T get(int i) const {
        return get(i, root, 0, size);
    }

    PersistentArray<T> set(int i, int x) const {
        return PersistentArray<T>(set(i, x, root, 0, size), size);
    }

private:
    struct Leaf {
        T data;
        explicit Leaf(const T& data): data(data) {}
    };

    struct Branch {
        void* left;
        void* right;
        Branch(void* l, void* r): left(l), right(r) {}
    };

    PersistentArray(void* root, int size): size(size), root(root) {}

    void* construct(const T& init, int l, int r) {
        if (r == l+1) { return new Leaf(init); }
        int m = (l + r) / 2;
        auto left  = construct(init, l, m);
        auto right = construct(init, m, r);
        return new Branch(left, right);
    }

    T get(int i, const void* node, int l, int r) const {
        if (l == i && r == i+1) { return ((const Leaf*)node)->data; }
        auto branch = (const Branch*)node;
        int m = (l + r) / 2;
        if (i < m) { return get(i, branch->left,  l, m); }
        else       { return get(i, branch->right, m, r); }
    }

    void* set(int i, int x, const void* node, int l, int r) const {
        if (l == i && r == i+1) { return new Leaf(x); }
        auto branch = (const Branch*)node;
        auto left  = branch->left;
        auto right = branch->right;
        int m = (l + r) / 2;
        if (i < m) { left  = set(i, x, branch->left,  l, m); }
        else       { right = set(i, x, branch->right, m, r); }
        return new Branch(left, right);
    }

private:
    int size;
    void* root;
};
