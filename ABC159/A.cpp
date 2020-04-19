#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    int N, M; cin >> N >> M;

    // 偶数+偶数
    // 奇数+奇数
    cout << N*(N-1)/2 + M*(M-1)/2 << endl;
}
