#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct UnionFind {
    vector<int> data;

    explicit UnionFind(int size) : data(size, -1) {}

    bool merge(int x, int y) {
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

    bool find(int x, int y) {
        return root(x) == root(y);
    }

    int root(int x) {
        return data[x] < 0 ? x : data[x] = root(data[x]);
    }

    int size(int x) {
        return -data[root(x)];
    }
};

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)

int main() {
    int N, M; cin >> N >> M;

    UnionFind uf(N);
    REP(i, M) {
        int A, B; cin >> A >> B; --A; --B;
        uf.merge(A, B);
    }

    int ans = 0;
    REP(i, N) {
        ans = max(ans, uf.size(i));
    }
    cout << ans << '\n';
}
