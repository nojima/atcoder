#include "lib/prelude.hpp"
#include "lib/io/string.hpp"

int main() {
    enum Choice { AB, BC, CA };

    int N = read_int();
    auto A = read_int();
    auto B = read_int();
    auto C = read_int();
    vector<Choice> S(N);
    REP(i, N) {
        auto s = read_word();
        if (s == "AB") S[i] = AB;
        else if (s == "AC") S[i] = CA;
        else if (s == "BC") S[i] = BC;
        else assert(false);
    }

    auto K = A+B+C;

    if (K <= 4) {
        // dp[i][a][b]: iターン目で(A,B,C)=(a,b,S-a-b)となる状態が実現可能か
        vector dp(N+1, vector(K+1, vector(K+1, char())));
        dp[0][A][B] = '*';
        REP(i, N) REP(a, K+1) REP(b, K+1) {
            if (!dp[i][a][b]) { continue; }
            int c = K-a-b;
            if (S[i] == AB) {
                if (a > 0) { dp[i+1][a-1][b+1] = 'B'; }
                if (b > 0) { dp[i+1][a+1][b-1] = 'A'; }
            }
            else if (S[i] == BC) {
                if (b > 0) { dp[i+1][a][b-1] = 'C'; }
                if (c > 0) { dp[i+1][a][b+1] = 'B'; }
            }
            else if (S[i] == CA) {
                if (a > 0) { dp[i+1][a-1][b] = 'C'; }
                if (c > 0) { dp[i+1][a+1][b] = 'A'; }
            }
        }
        int goal_a = -1, goal_b = -1;
        REP(a, K+1) REP(b, K+1) {
            if (dp[N][a][b]) {
                goal_a = a;
                goal_b = b;
                break;
            }
        }
        if (goal_a == -1) {
            cout << "No" << LF;
            return 0;
        }
        // 復元
        vector<char> ans(N);
        for (int i = N-1; i >= 0; --i) {
            //cout << goal_a << " " << goal_b << " " << K-goal_a-goal_b << LF;
            ans[i] = dp[i+1][goal_a][goal_b];
            if (S[i] == AB) {
                if (ans[i] == 'A') { --goal_a; ++goal_b; }
                else { ++goal_a; --goal_b; }
            }
            else if (S[i] == BC) {
                if (ans[i] == 'B') { --goal_b; }
                else { ++goal_b; }
            }
            else if (S[i] == CA) {
                if (ans[i] == 'A') { --goal_a; }
                else { ++goal_a; }
            }
        }
        cout << "Yes" << LF;
        REP(i, N) { cout << ans[i] << LF; }

    } else {
        // 貪欲法

        vector<int64_t> abc = {A, B, C};
        if (abc[S[0]] + abc[(S[0]+1)%3] == 0) {
            cout << "No" << LF;
            return 0;
        }

        vector<char> ans(N);
        REP(i, N) {
            int c1 = S[i], c2 = (S[i]+1)%3;
            if (abc[c1] < abc[c2]) {
                ++abc[c1];
                --abc[c2];
                ans[i] = c1 + 'A';
            } else {
                --abc[c1];
                ++abc[c2];
                ans[i] = c2 + 'A';
            }
            //cout << abc << LF;
        }

        cout << "Yes" << LF;
        REP(i, N) { cout << ans[i] << LF; }
    }
}
