#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define FOR(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define ALL(c) (c).begin(), (c).end()

inline int digit_to_int(char c) {
    return c - '0';
}

int main() {
    string S; cin >> S;

    string R = S;
    reverse(ALL(R));

    vector<int> M(S.size() + 1);
    M[0] = 0;
    int mag = 1;
    FOR(i, 1, M.size()) {
        M[i] = (M[i-1] + digit_to_int(R[i-1]) * mag) % 2019;
        mag = (10 * mag) % 2019;
    }

    vector<int> freq(2019);
    REP(i, M.size()) {
        freq[M[i]]++;
    }

    int64_t ans = 0;
    REP(i, freq.size()) {
        int64_t f = freq[i];
        ans += f * (f - 1) / 2;
    }

    cout << ans << endl;
}
