#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cassert>
//#include "../lib/debug.hpp"
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define ALL(c) (c).begin(), (c).end()

// 値 → 出現回数 を返す
vector<int> make_histogram(int M, const vector<int>& xs) {
    vector<int> histogram(M+1);
    for (int x : xs)
        histogram[x]++;
    return histogram;
}

// 出現回数 → {値} を返す
map<int, set<int>> make_freq2value(const vector<int>& histogram) {
    map<int, set<int>> ret;
    REP(value, histogram.size()) {
        int freq = histogram[value];
        ret[freq].insert(value);
    }
    return ret;
}

// 値 -> {出現位置} を返す
map<int, set<int>> make_index(const vector<int>& xs) {
    map<int, set<int>> ret;
    REP(i, xs.size())
        ret[xs[i]].insert(i);
    return ret;
}

int get_any(const map<int, set<int>>& index, int except) {
    for (auto& [v, ps] : index) {
        if (v != except) {
            return *ps.begin();
        }
    }
    assert(false);
}

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);

    int N; cin >> N;
    vector<int> A(N), B(N);
    REP(i, N) cin >> A[i];
    REP(i, N) cin >> B[i];

    vector<int> a_and_b;
    a_and_b.insert(a_and_b.end(), ALL(A));
    a_and_b.insert(a_and_b.end(), ALL(B));
    auto histogram_ab = make_histogram(N, a_and_b);

    for (int c : histogram_ab) {
        if (c >= N+1) {
            cout << "No\n";
            return 0;
        }
    }

    auto freq2value = make_freq2value(histogram_ab);
    auto index_a = make_index(A);
    auto index_b = make_index(B);

    vector<int> ans(N);
    for (int k = N; k >= 1; --k) {
        // 出現回数が k であるような x を取る。
        auto& xs = freq2value[k];
        int a_pos, b_pos;
        if (xs.size() == 2) {
            // そのような x が2つ存在する場合
            // 必ずその両方をペアにできるので、それを選ぶ。
            int x = *xs.begin(), y = *next(xs.begin());
            if (index_a.count(x)) {
                a_pos = *index_a[x].begin();
                b_pos = *index_b[y].begin();
            } else {
                a_pos = *index_a[y].begin();
                b_pos = *index_b[x].begin();
            }
        }
        else if (xs.size() == 1) {
            // そのような x がひとつだけ存在する場合
            // その x を含むようなペアを任意に選ぶ。
            auto x = *xs.begin();
            if (index_a.count(x)) {
                a_pos = *index_a[x].begin();
                b_pos = get_any(index_b, x);
            } else {
                b_pos = *index_b[x].begin();
                a_pos = get_any(index_a, x);
            }
        }
        else if (xs.size() == 0) {
            // そのような x が存在しない場合
            // どれを選んでもOK。
            auto find = [&](){
                for (auto& [v_a, ps_a] : index_a) {
                    for (auto& [v_b, ps_b] : index_b) {
                        if (v_a != v_b) {
                            return make_pair(*ps_a.begin(), *ps_b.begin());
                        }
                    }
                }
                assert(false);
            };
            tie(a_pos, b_pos) = find();
        }
        else { assert(false); }

        // データ構造の更新
        ans[a_pos] = B[b_pos];
        auto update_data_structures = [&](int pos, int value, map<int, set<int>>& index){
            int old_freq = histogram_ab[value];
            int new_freq = --histogram_ab[value];

            freq2value[old_freq].erase(value);
            freq2value[new_freq].insert(value);
            if (freq2value[old_freq].empty()) freq2value.erase(old_freq);

            index[value].erase(pos);
            if (index[value].empty()) index.erase(value);
        };
        update_data_structures(a_pos, A[a_pos], index_a);
        update_data_structures(b_pos, B[b_pos], index_b);
        //cout << "freq2value = " << freq2value << endl;
        //cout << a_pos << " " << b_pos << endl;
    }

    cout << "Yes\n";
    REP(i, ans.size()) {
        if (i != 0) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
}
