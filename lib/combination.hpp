#pragma once
#include "std.hpp"

template<class Int>
struct Combination {
    Int fact(int n) {
        if (n < (int)facts.size()) { return facts[n]; }
        for (int i = facts.size(); i <= n; ++i) {
            facts.emplace_back(facts[i-1] * i);
        }
        return facts[n];
    }
    Int inv_fact(int n) {
        if (n < (int)inv_facts.size()) { return inv_facts[n]; }
        fact(n); // fill facts[0..n]
        for (int i = inv_facts.size(); i <= n; ++i) {
            inv_facts.emplace_back(facts[i].inverse());
        }
        return inv_facts[n];
    }
    Int nPr(int n, int r) { return fact(n) * inv_fact(n-r); }
    Int nCr(int n, int r) { return fact(n) * inv_fact(r) * inv_fact(n-r); }
    Int nHr(int n, int r) { return nCr(n+r-1, r); }
private:
    vector<Int> facts = {1};
    vector<Int> inv_facts;
};
