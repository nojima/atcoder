#include "lib/prelude.hpp"

int main() {
    auto A = read_int();
    auto B = read_int();
    auto N = read_int();

    auto f = [A, B](int64_t x){ return (A*x)/B - A*(x/B); };

    // x = B-1 のときに最大
    // B-1が範囲外なときはできるだけ引数が大きいほうが良い
    if (B-1 <= N) {
        cout << f(B-1) << LF;
    } else {
        cout << f(N) << LF;
    }
}
