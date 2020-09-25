#include "lib/prelude.hpp"

int main() {
    auto N = read_int() - 1;

    string ans;
    while (N >= 0) {
        ans += N % 26 + 'a';
        N = N / 26 - 1;
    }
    reverse(ALL(ans));
    cout << ans << LF;
}
