#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long increment(long long a) {
    char s[30];
    bool overflow[30] = {};

    sprintf(s, "%lld", a);
    int len = strlen(s);
    reverse(s, s+len);

    s[0]++;
    for (int i = 0; i < len; ++i) {
        bool o = false;
        if (s[i] > '9') { o = true; }
        if (i != len-1 && abs(s[i] - s[i+1]) > 1) { o = true; }
        if (o) {
            // 繰り上がる
            overflow[i] = true;
            s[i+1]++;
        }
    }

    if (overflow[len-1]) {
        s[len] = '1';
        s[len+1] = '\0';
        overflow[len] = false;
        len++;
    }
    reverse(s, s+len);
    reverse(overflow, overflow+len);

    for (int i = 1; i < len; ++i) {
        if (overflow[i]) {
            s[i] = max(s[i-1]-1, (int)'0');
        }
    }

    sscanf(s, "%lld", &a);
    return a;
}

// 1,2,3,4,5,6,7,8,9,10,11,12,21,22,23,32,33,34,43,44,45,54,55,56,
// 65,66,67,76,77,78,87,88,89,98,99,100,101,110,111,112,121,122,123,132
int main() {
    int K; cin >> K;

    long long a = 1;
    for (int i = 1; i < K; ++i) {
        a = increment(a);
    }
    cout << a << endl;
}
