use proconio::input;

fn main() {
    input! {
        n: usize,
        k: usize,
        heights: [i64; n],
    }

    let jump_cost = |i: usize, j: usize| (heights[i] - heights[j]).abs();

    let mut dp = vec![0; n];
    for i in 0..n {
        dp[i] = (1..=k)
            .filter(|j| i >= *j)
            .map(|j| dp[i - j] + jump_cost(i - j, i))
            .min()
            .unwrap_or(0);
    }

    println!("{}", dp[n - 1]);
}
