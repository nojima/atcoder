#include "lib/prelude.hpp"
#include "lib/io/string.hpp"

using int128 = __int128_t;

int main() {
    int128 A = read_int();
    string B = read_word();

    int128 C = 0;
    REP(i, B.size()) {
        if (B[i] == '.') continue;
        C = (C * 10) + (B[i] - '0');
    }
    cout << int64_t(A*C/100) << endl;
}
