#include "lib/prelude.hpp"

int main() {
    int K; cin >> K;

    int a = 7 % K;
    REP(i, K+1) {
        if (a == 0) {
            cout << i+1 << LF;
            return 0;
        }
        a = (10 * a + 7) % K;
    }
    cout << -1 << LF;
}
