use std::{io::Read, time::{Duration, Instant}};
use rand::{Rng, SeedableRng};
use rand::rngs::SmallRng;

struct Ad {
    x: i32,
    y: i32,
    r: i32,
}


struct Area {
    x0: i32,
    y0: i32,
    x1: i32,
    y1: i32,
}

fn overlapps_1d(l1: i32, r1: i32, l2: i32, r2: i32) -> bool {
    l2 <= r1 && l1 <= r2
}

fn contains_1d(l: i32, r: i32, x: i32) -> bool {
    l <= x && x < r
}

impl Area {
    fn overlapps(&self, other: &Area) -> bool {
        overlapps_1d(self.x0, self.x1, other.x0, other.x1)
            && overlapps_1d(self.y0, self.y1, other.y0, other.y1)
    }

    fn contains(&self, x: i32, y: i32) -> bool {
        contains_1d(self.x0, self.x1, x)
            && contains_1d(self.y0, self.y1, y)
    }

    fn size(&self) -> i32 {
        (self.x1 - self.x0) * (self.y1 - self.y0)
    }
}

fn read_input() -> Vec<Ad> {
    let mut buffer = String::new();
    std::io::stdin().read_to_string(&mut buffer).unwrap();
    let mut iter = buffer.split_ascii_whitespace();

    let n = iter.next().unwrap().parse::<i32>().unwrap();
    (0..n).map(|_| {
        let x = iter.next().unwrap().parse::<i32>().unwrap();
        let y = iter.next().unwrap().parse::<i32>().unwrap();
        let r = iter.next().unwrap().parse::<i32>().unwrap();
        Ad { x, y, r }
    }).collect::<Vec<_>>()
}

fn make_initial_solution(ads: &[Ad]) -> Vec<Area> {
    ads.iter().map(|ad|
        Area {
            x0: ad.x,
            y0: ad.y,
            x1: ad.x + 1,
            y1: ad.y + 1,
        }
    ).collect::<Vec<_>>()
}

fn is_valid_solution(solution: &[Area]) -> bool {
    for i in 0..solution.len() {
        let area = &solution[i];
        if !contains_1d(0, 10001, area.x0) {
            return false;
        }
        if !contains_1d(0, 10001, area.x1) {
            return false;
        }
        if !contains_1d(0, 10001, area.y0) {
            return false;
        }
        if !contains_1d(0, 10001, area.y1) {
            return false;
        }
        if !(area.x0 <= area.x1) {
            return false;
        }
        if !(area.y0 <= area.y1) {
            return false;
        }
        for j in i+1..solution.len() {
            if solution[i].overlapps(&solution[j]) {
                return false
            }
        }
    }
    true
}

fn pow2(x: f64) -> f64 { x * x }

fn calculate_score(ads: &[Ad], solution: &[Area]) -> i64 {
    let mut score = 0.0;
    for (ad, area) in ads.iter().zip(solution.iter()) {
        let s = area.size();
        let p = if area.contains(ad.x, ad.y) {
            let a = ad.r.min(s) as f64;
            let b = ad.r.max(s) as f64;
            1.0 - pow2(1.0 - a / b)
        } else {
            0.0
        };
        score += p;
    }

    (1e9 * score / (ads.len() as f64)).round() as i64
}

fn output_solution(solution: &[Area]) {
    for area in solution.iter() {
        println!("{} {} {} {}", area.x0, area.y0, area.x1, area.y1);
    }
}

fn hill_climbing(ads: &[Ad]) -> Vec<Area> {
    let seed = 0x322845c730d6abacu64;
    let mut rng = SmallRng::seed_from_u64(seed);

    let mut solution = make_initial_solution(&ads);

    let start_at = Instant::now();
    let deadline = start_at + Duration::from_millis(4980);

    let mut iter = 0;
    loop {
        iter += 1;

        if iter % 100 == 0 {
            // 時間切れか調べる
            let now = Instant::now();
            if now >= deadline {
                break;
            }
        }

        // TODO: 解を改善する
    }

    solution
}

fn main() {
    let ads = read_input();
    let solution = hill_climbing(&ads);
    output_solution(&solution);

    if is_valid_solution(&solution) {
        eprintln!("Score: {}", calculate_score(&ads, &solution));
    } else {
        eprintln!("Invalid solution!!!!");
    }
}
