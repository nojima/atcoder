#include "lib/prelude.hpp"
#include "lib/bit.hpp"
#include "lib/binary_search.hpp"

template<class T> union Node;

template<class T>
struct Leaf {
    const T data;
    explicit Leaf(const T& data) noexcept : data(data) {}
};

template<class T>
struct Branch {
    const Node<T>* left;
    const Node<T>* right;
    Branch(const Node<T>* left, const Node<T>* right) noexcept
        : left(left), right(right) {}
};

template<class T>
union Node {
    Leaf<T>   leaf;
    Branch<T> branch;
};

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
        if (r == l+1) { return (Node<T>*) new Leaf<T>(init); }
        int m = (l + r) / 2;
        auto left  = construct(init, l, m);
        auto right = construct(init, m, r);
        return (Node<T>*) new Branch<T>(left, right);
    }
    T get(int i, const Node<T>* node, int l, int r) const {
        if (l == i && r == i+1) { return node->leaf.data; }
        int m = (l + r) / 2;
        if (i < m) { return get(i, node->branch.left,  l, m); }
        else       { return get(i, node->branch.right, m, r); }
    }
    Node<T>* set(int i, int x, const Node<T>* node, int l, int r) const {
        if (l == i && r == i+1) { return (Node<T>*) new Leaf<T>(x); }
        auto left  = node->branch.left;
        auto right = node->branch.right;
        int m = (l + r) / 2;
        if (i < m) { left  = set(i, x, node->branch.left,  l, m); }
        else       { right = set(i, x, node->branch.right, m, r); }
        return (Node<T>*) new Branch<T>(left, right);
    }

private:
    int size;
    Node<T>* root;
};

int N;
vector<int64_t> A;
vector<vector<int>> graph;
vector<int> ans;

void dp(int v, int len, PersistentArray<int> lis) {
    if (ans[v] != -1) return;
    int ll = find_minimum_solution(0, N+1, [&lis, a=A[v]](int l){
        return a < lis.get(l);
    });
    if (ll >= 1 && lis.get(ll-1) < A[v]) {
        lis = lis.set(ll, A[v]);
    }
    ans[v] = find_maximum_solution(0, N, [&lis](int l){
        return lis.get(l) < numeric_limits<int>::max();
    });
    for (int w : graph[v]) {
        dp(w, len+1, lis);
    }
}

int main() {
    N = read_int();
    A.resize(N);
    REP(i, N) A[i] = read_int();
    graph.resize(N);
    REP(i, N-1) {
        int u = read_int()-1;
        int v = read_int()-1;
        graph[u].emplace_back(v);
        graph[v].emplace_back(u);
    }

    ans.resize(N);
    fill(ALL(ans), -1);

    // lis[l]: 長さ l の最長増加部分列の高さの最小値
    PersistentArray lis(N+1, numeric_limits<int>::max());
    lis = lis.set(0, 0);
    dp(0, 1, lis);

    REP(i, N) cout << ans[i] << LF;
}
