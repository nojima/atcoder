#include <algorithm>
#include <iostream>
#include <vector>
#include <limits>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)

vector<vector<int>> decompose_to_loops(const vector<int>& P) {
    vector<vector<int>> ret;
    vector<bool> visited(P.size());

    REP(s, P.size()) {
        if (visited[s]) { continue; }

        vector<int> loop;
        int v = s;
        do {
            loop.push_back(v);
            visited[v] = true;
            v = P[v];
        } while (v != s);
        ret.emplace_back(move(loop));
    }

    return ret;
}

template <typename Func>
inline vector<int64_t> make_cumsum(size_t n, Func get_ith_value) {
    vector<int64_t> cumsum(n+1);
    REP(i, cumsum.size()) {
        cumsum[i] = (i == 0) ? 0 : cumsum[i-1] + get_ith_value(i-1);
    }
    return cumsum;
}

// [first, last] の和を返す
int64_t sum_of(const vector<int64_t>& cumsum, int first, int last) {
    return cumsum[last+1] - cumsum[first];
}

int main() {
    cin.tie(nullptr); ios::sync_with_stdio(false);

    int N; cin >> N;
    int64_t K; cin >> K;
    vector<int> P(N);
    REP(i, N) {
        cin >> P[i];
        --P[i];
    }
    vector<int64_t> C(N);
    REP(i, N) {
        cin >> C[i];
    }

    int64_t max_sum = numeric_limits<int64_t>::min();

    for (const auto& loop : decompose_to_loops(P)) {
        int64_t loop_size = loop.size();
        auto cumsum = make_cumsum(loop_size, [&](int i) { return C[loop[i]]; });

        for (int64_t k = 0; k < min(K, loop_size); ++k) {
            int64_t bonus = max<int64_t>(0, ((K-k-1) / loop_size) * cumsum[loop_size]);

            REP(s, loop_size) {
                int64_t sum;
                if (s + k < loop_size) {
                    sum = sum_of(cumsum, s, s + k);
                } else {
                    sum = sum_of(cumsum, s, loop_size-1) + sum_of(cumsum, 0, s+k-loop_size);
                }
                max_sum = max(max_sum, sum + bonus);
            }
        }
    }

    cout << max_sum << '\n';
}
