#pragma once
#include "std.hpp"
#include <boost/operators.hpp>

struct BitSet : private boost::operators<BitSet> {
    uint32_t S;

public:
    explicit BitSet(uint32_t S): S(S) {}

    // 集合 {0, 1, .., n-1} を返す。
    static inline BitSet from_size(int n) noexcept {
        return BitSet((1 << n) - 1);
    }

    // ∅ を返す
    static inline BitSet empty() noexcept {
        return BitSet(0);
    }

    // i ∈ S ならば true を返す。
    inline constexpr bool operator[](int i) const noexcept {
        return (S >> i) & 1;
    }

    // S ⊆ other ならば true を返す。
    inline bool is_subset_of(BitSet other) const noexcept {
        return (S & other.S) == S;
    }

    // S ∪ {i} を返す。
    [[nodiscard]] inline BitSet insert(int i) const noexcept {
        return BitSet(S | (1 << i));
    }

    // S \ {i} を返す。
    [[nodiscard]] inline BitSet remove(int i) const noexcept {
        return BitSet(S & ~(1 << i));
    }

    // S \ other を返す。
    [[nodiscard]] inline BitSet exclude(BitSet other) const noexcept {
        return BitSet(S & ~other.S);
    }

    // |S| を返す。
    inline constexpr int size() const noexcept {
        return __builtin_popcount(S);
    }

    // 生の表現を返す。
    inline constexpr uint32_t raw() const noexcept {
        return S;
    }

    // S の要素を列挙する。
    template <class Func>
    void foreach_element(Func f) {
        for (uint32_t T = S; T; T -= T & -T) {
            f(__builtin_ffs(T) - 1);
        }
    }

    // S のすべての部分集合(∅ と S 自身を含む)を列挙する。
    template <class Func>
    void foreach_subset(Func f) {
        uint32_t whole = S;
        uint32_t subset = 0;
        for (;;) {
            f(BitSet(subset));
            if (subset == whole) { return; }
            subset = (subset - whole) & whole;
        }
    }

    // Operators
    inline bool    operator< (const BitSet& rhs) const noexcept { return S <  rhs.S; }
    inline bool    operator==(const BitSet& rhs) const noexcept { return S == rhs.S; }
    inline BitSet& operator|=(const BitSet& rhs) noexcept { S |= rhs.S; return *this; }
    inline BitSet& operator&=(const BitSet& rhs) noexcept { S &= rhs.S; return *this; }
    inline BitSet& operator^=(const BitSet& rhs) noexcept { S ^= rhs.S; return *this; }
};

// 集合 {0, 1, .., n-1} のすべての部分集合を列挙する。
template <class Func>
void foreach_subset(int n, Func f) {
    for (uint32_t S = 0; S < (uint32_t)(1 << n); ++S) {
        f(BitSet(S));
    }
}

// 要素数が k であるような {0, 1, .., n-1} の部分集合をすべて列挙する。
template <class Func>
void foreach_combination(int n, int k, Func f) {
    // 蟻本 p144 より
    uint32_t subset = (1 << k) - 1;
    while (subset < (uint32_t)(1 << n)) {
        f(BitSet(subset));
        uint32_t x = subset & -subset; // 最下位の1
        uint32_t y = subset + x;       // 最下位の1が連続している区間を繰り上げたもの
        uint32_t z = subset & ~y;      // 最下位の1が連続している区間
        subset = ((z / x) >> 1) | y;
    }
}
