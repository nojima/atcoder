#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

bool kaibun(string str) {
    int l = str.length();
    for (int i = 0; i < l; ++i) {
        if (str[i] != str[l-i-1]) {
            return false;
        }
    }
    return true;
}

int main() {
    string S; cin >> S;

    int N = S.length();
    bool ok = kaibun(S)
        && kaibun(S.substr(0, (N-1)/2))
        && kaibun(S.substr((N+3)/2-1));
    if (ok) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
}
