#include "knuth_morris_pratt.hpp"
#include "debug.hpp"

int main() {
    vector pattern = {1, 2, 3, 9, 1, 2, 3};
    vector text    = {1, 2, 3, 9, 1, 2, 3, 9, 1, 2, 3};

    auto pma = build_pma(pattern);
    cout << pma << endl;

    find_all_matches(pma, pattern, text, [](int index){
        cout << index << endl;
    });
}
