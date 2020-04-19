#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int main() {
    int N; cin >> N;
    char s[100];
    sprintf(s, "%d", N);
    int len = strlen(s);
    bool ok = false;
    for (int i = 0; i < len; ++i) {
        if (s[i] == '7') {
            ok = true;
        }
    }
    if (ok) {
        puts("Yes");
    } else {
        puts("No");
    }
    return 0;
}
