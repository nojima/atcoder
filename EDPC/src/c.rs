use std::cmp::max;
use proconio::input;

fn main() {
    input! {
        n: usize,
        hapiness: [[i64; 3]; n],
    }

    let mut dp = vec![vec![0 as i64; 3]; n];

    for d in 0..n {
        for a in 0..3 {
            if d == 0 {
                dp[d][a] = hapiness[0][a];
            } else {
                dp[d][a] = hapiness[d][a] + max(dp[d-1][(a+1) % 3], dp[d-1][(a+2) % 3]);
            }
        }
    }

    println!("{}", dp[n-1].iter().max().unwrap());
}
