#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define ALL(c) (c).begin(), (c).end()

int main() {
    int N; cin >> N;
    int c = 0;
    bool ok = false;
    REP(i, N) {
        int d1, d2; cin >> d1 >> d2;
        if (d1 == d2) {
            ++c;
            if (c == 3) ok = true;
        } else {
            c = 0;
        }
    }
    if (ok) cout << "Yes" << endl;
    else cout << "No" << endl;
}
