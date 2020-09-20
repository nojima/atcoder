#pragma once
#include "../std.hpp"

char read_char() {
    int ch = getchar_unlocked();
    while (isspace(ch)) { ch = getchar_unlocked(); }
    return ch;
}
