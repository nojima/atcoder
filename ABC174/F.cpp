#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define ALL(c) (c).begin(), (c).end()

template <class T, class Compare>
vector<int> sort_index(const vector<T>& v, Compare comp) {
    vector<int> index(v.size());
    REP(i, v.size()) index[i] = i;
    sort(ALL(index), [&](int i, int j) { return comp(v[i], v[j]); });
    return index;
}

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

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);

    int N, Q; cin >> N >> Q;
    vector<int> C(N);
    REP(i, N) cin >> C[i];
    vector<pair<int, int>> queries(Q);
    REP(i, Q) {
        cin >> queries[i].first >> queries[i].second;
        queries[i].first--; queries[i].second--;
    }

    auto index = sort_index(queries, [](const auto& p1, const auto& p2) {
        return make_pair(p1.second, p1.first) < make_pair(p2.second, p2.first);
    });

    // 色 → その色を持つ玉の中で最も右にある玉の位置
    vector<int> rightmost(N+1, -1);
    // その位置に最右玉が存在するなら 1、そうでないなら 0
    FenwickTree<int> ft(N);

    vector<int> ans(Q);
    int k = 0;
    REP(x, N) {
        // データ構造を更新
        int c = C[x];
        int old_pos = rightmost[c];
        int new_pos = x;
        if (old_pos != -1) ft.add(old_pos, -1);
        ft.add(new_pos, 1);
        rightmost[c] = new_pos;

        // クエリを処理
        for (; k < Q && queries[index[k]].second == x; ++k) {
            auto [l, r] = queries[index[k]];
            ans[index[k]] = ft.sum(l, r);
        }
    }

    REP(i, Q) cout << ans[i] << '\n';
}
