#include "bit_set.hpp"
#include "debug.hpp"

int main() {
    vector<uint32_t> actual1;
    foreach_subset_of(BitSet(0b1101), [&](BitSet S) {
        actual1.push_back(S.data);
    });
    vector<uint32_t> expected1 = {
        0b0000, 0b0001, 0b0100, 0b0101,
        0b1000, 0b1001, 0b1100, 0b1101,
    };
    assert(actual1 == expected1);

    vector<uint32_t> actual2;
    foreach_subset_with_size(5, 3, [&](BitSet S) {
        actual2.push_back(S.data);
    });
    // C(5, 3) = 5*4 / 2*1 = 10
    vector<uint32_t> expected2 = {
        0b00111, 0b01011, 0b01101, 0b01110, 0b10011,
        0b10101, 0b10110, 0b11001, 0b11010, 0b11100,
    };
    assert(actual2 == expected2);
}
