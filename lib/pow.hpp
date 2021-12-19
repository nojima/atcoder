#pragma once

// base の exponent 乗を返す。
template <class T, class Product>
T generic_pow(
    T       base,
    int64_t exponent,
    T       identity, // product の単位元
    Product product   // 二項演算子 (T, T) -> T
) {
    T ans = identity;
    while (exponent > 0) {
        if (exponent & 1) {
            ans = product(ans, base);
        }
        base = product(base, base);
        exponent >>= 1;
    }
    return ans;
}
