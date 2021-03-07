#pragma once
#include "std.hpp"
#include "bit.hpp"

// xoshiro256++
// 出典: https://prng.di.unimi.it/xoshiro256plusplus.c
class Xoshiro256 {
    uint64_t s[4] = {
        0xa4b530bda1198f5dULL,
        0x4d4b9a7df80033fdULL,
        0x2b54801d0136fa9eULL,
        0x7594f134ce0ab042ULL,
    };

public:
    uint64_t operator()() noexcept {
        const uint64_t result = rotl(s[0] + s[3], 23) + s[0];
        const uint64_t t = s[1] << 17;
        s[2] ^= s[0];
        s[3] ^= s[1];
        s[1] ^= s[2];
        s[0] ^= s[3];
        s[2] ^= t;
        s[3] = rotl(s[3], 45);
        return result;
    }

    using result_type = uint64_t;
    constexpr inline uint64_t min() noexcept { return 0; }
    constexpr inline uint64_t max() noexcept { return numeric_limits<uint64_t>::max(); }
};
