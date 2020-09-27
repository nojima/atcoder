#include "lib/prelude.hpp"

int main() {
    auto X = read_int();
    for (int64_t A = -118; A <= 119; ++A) {
        for (int64_t B = -119; B <= 119; ++B) {
            if (A*A*A*A*A - B*B*B*B*B == X) {
                cout << A << " " << B << LF;
                return 0;
            }
        }
    }
}
