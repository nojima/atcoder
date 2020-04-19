#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <climits>
using namespace std;

inline bool test_bit(unsigned x, int i) {
    return (x >> i) & 1;
}

int main() {
    int H, W, K; cin >> H >> W >> K;
    vector<vector<bool>> choco(H+1, vector<bool>(W+1));
    for (int y = 1; y <= H; ++y) {
        for (int x = 1; x <= W; ++x) {
            char ch; cin >> ch;
            choco[y][x] = ch == '1';
        }
    }

    vector<vector<int>> sum(H+1, vector<int>(W+1));
    for (int y = 1; y <= H; ++y) {
        for (int x = 1; x <= W; ++x) {
            sum[y][x] = sum[y-1][x] + sum[y][x-1] - sum[y-1][x-1];
        }
    }

    int ans = INT_MAX;
    for (unsigned h_slice = 0; h_slice < (unsigned)(1 << H); ++h_slice) {
        int h_split = __builtin_popcount(h_slice);
        int v_split = 0;
        vector<int> count(H+1);
        vector<int> next(H+1);
        for (int x = 1; x <= W; ++x) {
            int cut_y = 1;
            fill(next.begin(), next.end(), 0);
            for (int y = 1; y <= H; ++y) {
                if (test_bit(h_slice, y)) { cut_y = y; }
                if (choco[y][x]) { next[cut_y]++; }
            }
            //cout << "next[1]" << ": " << next[1] << endl;
            //cout << "count[1]" << ": " << count[1] << endl;
            for (int y = 1; y <= H; ++y) {
                if (next[y] > K) {
                    goto next_candidate;
                }
            }
            bool should_split = false;
            for (int y = 1; y <= H; ++y) {
                if (count[y] + next[y] > K) {
                    should_split = true;
                }
                count[y] += next[y];
            }
            if (should_split) {
                v_split++;
                count = next;
            }
        }

        //cout << h_slice << ": " << v_split << endl;
        if (h_split + v_split < ans) {
            ans = h_split + v_split;
        }

next_candidate:;
    }

    cout << ans << endl;
}
