#pragma once
#include "std.hpp"

template<class T> union Node;

template<class T>
struct Leaf {
    T data;
};

template<class T>
struct Branch {
    Node<T>* left;
    Node<T>* right;
};

template<class T>
union Node {
    Leaf<T>   leaf;
    Branch<T> branch;
};

template<class T>
Node<T>* new_leaf(const T& data) {
    auto node = new Node<T>;
    node->leaf.data = data;
    return node;
}

template<class T>
Node<T>* new_branch(Node<T>* left, Node<T>* right) {
    auto node = new Node<T>;
    node->branch.left = left;
    node->branch.right = right;
    return node;
}

template<class T>
struct PersistentArray {
    PersistentArray(int n, const T& init)
        : size(bit_ceil(n)), root(construct(init, 0, size)) {}

    T get(int i) const {
        return get(i, root, 0, size);
    }

    PersistentArray<T> set(int i, int x) {
        return PersistentArray<T>(set(i, x, root, 0, size), size);
    }

private:
    PersistentArray(Node<T>* root, int size): size(size), root(root) {}

    Node<T>* construct(const T& init, int l, int r) {
        if (r == l+1) { return new_leaf(init); }
        int m = (l + r) / 2;
        auto left  = construct(init, l, m);
        auto right = construct(init, m, r);
        return new_branch(left, right);
    }

    T get(int i, const Node<T>* node, int l, int r) const {
        if (l == i && r == i+1) { return node->leaf.data; }
        int m = (l + r) / 2;
        if (i < m) { return get(i, node->branch.left,  l, m); }
        else       { return get(i, node->branch.right, m, r); }
    }

    Node<T>* set(int i, int x, const Node<T>* node, int l, int r) const {
        if (l == i && r == i+1) { return new_leaf(x); }
        auto left  = node->branch.left;
        auto right = node->branch.right;
        int m = (l + r) / 2;
        if (i < m) { left  = set(i, x, node->branch.left,  l, m); }
        else       { right = set(i, x, node->branch.right, m, r); }
        return new_branch(left, right);
    }

private:
    int size;
    Node<T>* root;
};
