#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define REP(i, n) for (int i = 0; i < (int)(n); ++i)
#define ALL(c) (c).begin(), (c).end()

int main() {
    string s; cin >> s;
    if (s[s.size()-1] == 's')
        cout << s << "es" << endl;
    else
        cout << s << 's' << endl;
}
