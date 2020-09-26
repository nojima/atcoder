#pragma once
#include "std.hpp"

template<class Int>
struct Combination {
    vector<Int> facts = {1};
    Int fact(int n) {
        if (n < (int)facts.size()) { return facts[n]; }
        for (int i = facts.size(); i <= n; ++i) {
            facts.emplace_back(facts[i-1] * i);
        }
        return facts[n];
    }
    Int nCr(int n, int r) { return fact(n) / (fact(r) * fact(n-r)); }
    Int nHr(int n, int r) { return nCr(n+r-1, r); }
};
