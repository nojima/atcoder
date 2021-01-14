#include "lib/prelude.hpp"

int main() {
    auto X = read_int();
    auto Y = read_int();

    if (X > Y) swap(X, Y);
    if (X + 3 > Y)
        cout << "Yes\n";
    else
        cout << "No\n";
}
