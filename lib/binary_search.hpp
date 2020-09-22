#pragma once
#include "std.hpp"

// pred(x) を区間[a, b)で定義された単調増加なbool値関数とする。
// このとき pred(x) = true となるような最小の x を返す。
// そのような x が存在しないときは b を返す。
template <class Pred>
int64_t find_minimum_solution(int64_t a, int64_t b, Pred pred) {
    // 不変条件: i<a ⇒ pred(i)=false, b<=i ⇒ pred(i)=true
    if (a == b) return b;
    int64_t m = a + (b - a) / 2;
    if (pred(m))
        return find_minimum_solution(a, m, pred);
    else
        return find_minimum_solution(m+1, b, pred);
}

// pred(x) を区間(a, b]で定義された単調減少なbool値関数とする。
// (定義域に注意!!)
// このとき pred(x) = true となるような最大の x を返す。
// そのような x が存在しないときは a を返す。
template <class Pred>
int64_t find_maximum_solution(int64_t a, int64_t b, Pred pred) {
    // 不変条件: i<=a ⇒ pred(i)=true, b<i ⇒ pred(i)=false
    if (a == b) return a;
    int64_t m = a + (b - a + 1) / 2;
    if (pred(m))
        return find_maximum_solution(m, b, pred);
    else
        return find_maximum_solution(a, m-1, pred);
}
