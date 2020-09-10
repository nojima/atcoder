#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define ALL(c) (c).begin(), (c).end()

inline bool is_valid(int i, int j) {
    return j >= 0 && i/2 - 1 <= j && j <= (i+1) / 2;
}

int main() {
    int N; cin >> N;
    vector<int> A(N);
    REP(i, N) cin >> A[i];

    vector<vector<int64_t>> dp(3, vector<int64_t>((N+1)/2 + 1));
    dp[1][0] = 0;
    dp[1][1] = A[0];
    for (int i = 2; i <= N; ++i) {
        for (int j = i/2 - 1; j <= (i+1) / 2; ++j) {
            int64_t v1 = is_valid(i-2, j-1) ? dp[(i-2)%3][j-1] + A[i-1]
                                            : numeric_limits<int64_t>::min();
            int64_t v2 = is_valid(i-1, j) ? dp[(i-1)%3][j]
                                          : numeric_limits<int64_t>::min();
            dp[i%3][j] = max(v1, v2);
        }
    }
    cout << dp[N%3][N/2] << '\n';
}
