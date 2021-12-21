#include "bit_set.hpp"
#include "debug.hpp"

int main() {
    vector<uint32_t> actual1;
    BitSet(0b1101).foreach_subset([&](BitSet S) {
        actual1.push_back(S.raw());
    });
    vector<uint32_t> expected1 = {
        0b0000, 0b0001, 0b0100, 0b0101,
        0b1000, 0b1001, 0b1100, 0b1101,
    };
    assert(actual1 == expected1);

    vector<uint32_t> actual2;
    foreach_combination(5, 3, [&](BitSet S) {
        actual2.push_back(S.raw());
    });
    // C(5, 3) = 5*4 / 2*1 = 10
    vector<uint32_t> expected2 = {
        0b00111, 0b01011, 0b01101, 0b01110, 0b10011,
        0b10101, 0b10110, 0b11001, 0b11010, 0b11100,
    };
    assert(actual2 == expected2);

    vector<int> actual3;
    BitSet(0b010011010).foreach_element([&](int i) {
        actual3.push_back(i);
    });
    vector<int> expected3 = {1, 3, 4, 7};
    assert(actual3 == expected3);
}
