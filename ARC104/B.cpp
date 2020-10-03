#include "lib/prelude.hpp"
#include "lib/io/string.hpp"

int main() {
    int N = read_int();
    string S = read_word();

    REP(i, N) {
        char c = S[i];
        if (c == 'A') S[i] = 0;
        if (c == 'T') S[i] = 1;
        if (c == 'C') S[i] = 2;
        if (c == 'G') S[i] = 3;
    }

    // 以下を満たすような部分文字列の数を数える
    //    'A'と'T'の数が等しい
    //    'C'と'G'の数が等しい

    int ans = 0;
    REP(i, N) {
        vector<int> freq(4);
        FOR(j, i, N) {
            // S[i..j] が条件を満たすか調べる
            ++freq[S[j]];
            if (freq[0] == freq[1] && freq[2] == freq[3]) {
                ++ans;
            }
        }
    }
    cout << ans << endl;
}
