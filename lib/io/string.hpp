#pragma once
#include "../std.hpp"

string read_word() {
    string ret;
    int ch = getchar_unlocked();
    while (isspace(ch)) { ch = getchar_unlocked(); }
    for (; ch != EOF && !isspace(ch); ch = getchar_unlocked())
        ret += ch;
    ungetc(ch, stdin);
    return ret;
}
