#pragma once
#include "std.hpp"

using PMA = vector<int>;

template<class SymbolSeq>
PMA build_pma(const SymbolSeq& pattern) {
    // pma[i]: 以下を満たす最大の l
    //         pattern[0..l) == pattern[i-l..i)
    PMA pma(pattern.size()+1);
    pma[0] = -1;
    int j = -1;
    for(int i = 0; i < (int)pattern.size(); ++i) {
        while(j >= 0 && pattern[j] != pattern[i]) { j = pma[j]; }
        ++j;
        pma[i+1] = j;
    }
    return pma;
}

template<class SymbolSeq, class Func>
void find_all_matches(
    const PMA& pma,
    const SymbolSeq& pattern,
    const SymbolSeq& text,
    Func on_match
) {
    int j = 0;
    for(int i = 0; i < (int)text.size(); ++i) {
        while(j >= 0 && pattern[j] != text[i]) { j = pma[j]; }
        ++j;
        if(j == (int)pattern.size()) {
            on_match(i - (int)pattern.size() + 1);
            j = pma[j];
        }
    }
}
