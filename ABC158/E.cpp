#include "lib/prelude.hpp"
#include "lib/io/string.hpp"

int main() {
    int64_t N = read_int();
    int64_t P = read_int();
    string S = read_word();

    REP(i, S.size()) S[i] -= '0';
    reverse(ALL(S));

    if (P == 2 || P == 5) {
        int64_t ans = 0;
        REP(i, N) {
            if (S[i] % P == 0) {
                ans += N - i;
            }
        }
        cout << ans << LF;
    } else {
        vector<int64_t> freq(P+1);
        int64_t num = 0;
        int64_t ten = 1;
        int64_t ans = 0;
        REP(j, N) {
            num = (num + (S[j] * ten) % P) % P;
            if (num == 0) { ++ans; }
            ans += freq[num];
            ++freq[num];
            ten = (ten * 10) % P;
        }
        cout << ans << LF;
    }
}
