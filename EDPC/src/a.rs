use proconio::input;
use std::cmp::min;

fn main() {
    input! {
        n: usize,
        heights: [i64; n],
    }

    let jump_cost = |i: usize, j: usize| (heights[i] - heights[j]).abs();

    let mut dp = vec![0; n];
    for i in 1..n {
        if i == 1 {
            dp[i] = jump_cost(0, 1);
        } else {
            dp[i] = min(
                dp[i - 2] + jump_cost(i - 2, i),
                dp[i - 1] + jump_cost(i - 1, i),
            );
        }
    }

    println!("{}", dp[n - 1]);
}
