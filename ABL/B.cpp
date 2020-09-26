#include "lib/prelude.hpp"

int main() {
    auto A = read_int();
    auto B = read_int();
    auto C = read_int();
    auto D = read_int();

    if (B < C || D < A)
        cout << "No" << LF;
    else
        cout << "Yes" << LF;
}
