#pragma once

// n以上の最小の2の冪を返す。
constexpr int bit_ceil(int n) noexcept {
    int ret = 1;
    while (ret < n) { ret *= 2; }
    return ret;
}
