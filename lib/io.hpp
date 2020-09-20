#include <cctype>
#include <cstdio>
#include <cstdint>
#include <string>
using namespace std;

#pragma region io.hpp

int64_t read_int() {
    int64_t ret = 0, sgn = 1;
    int ch = getchar_unlocked();
    while (isspace(ch)) { ch = getchar_unlocked(); }
    if (ch == '-') { sgn = -1; ch = getchar_unlocked(); }
    for (; isdigit(ch); ch = getchar_unlocked())
        ret = (ret * 10) + (ch - '0');
    ungetc(ch, stdin);
    return sgn * ret;
}

char read_char() {
    int ch = getchar_unlocked();
    while (isspace(ch)) { ch = getchar_unlocked(); }
    return ch;
}

string read_word() {
    string ret;
    int ch = getchar_unlocked();
    while (isspace(ch)) { ch = getchar_unlocked(); }
    for (; ch != EOF && !isspace(ch); ch = getchar_unlocked())
        ret += ch;
    ungetc(ch, stdin);
    return ret;
}

#pragma endregion io.hpp
