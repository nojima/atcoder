#pragma once
#include "std.hpp"

// 区間[a, b)の中で最初に pred(x) = true となるような x を返す。
// そのような x が存在しないときは b を返す。
template <class Pred>
int64_t bin_search(int64_t a, int64_t b, Pred pred) {
    // 不変条件: i<a ⇒ pred(i)=false, i>=b ⇒ pred(i)=true
    if (a == b) return b;
    int64_t m = a + (b - a) / 2;
    if (pred(m))
        return bin_search(a, m, pred);
    else
        return bin_search(m+1, b, pred);
}
