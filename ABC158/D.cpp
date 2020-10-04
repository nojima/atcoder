#include "lib/prelude.hpp"
#include "lib/io/char.hpp"
#include "lib/io/string.hpp"

int main() {
    string tail = read_word();
    string head;

    int Q = read_int();
    REP(q, Q) {
        int t = read_int();
        if (t == 1) {
            swap(head, tail);
        } else {
            int f = read_int();
            char c = read_char();
            if (f == 1) {
                head.push_back(c);
            } else {
                tail.push_back(c);
            }
        }
    }

    reverse(ALL(head));
    cout << head << tail << LF;
}
