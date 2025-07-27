use std::io::{BufRead, BufReader};
use std::fs::File;
use std::collections::VecDeque;

fn main() {
    let mut reader = BufReader::new(File::open("data.txt").unwrap());

    let mut grid = [['.'; 71]; 71]; 
    let mut visited = [[false; 71]; 71];

    for _ in 0..1024 {
        let mut line = String::new();
        reader.read_line(&mut line).unwrap();

        if let Ok((x, y)) = sscanf::sscanf!(&line.trim(), "{},{}", i32, i32) {
            grid[y as usize][x as usize] = '#';
        }
    }

    let dx = [-1, 1, 0, 0];
    let dy = [0, 0, 1, -1];

    let mut queue: VecDeque<(i32, i32, i32)> = VecDeque::new();

    queue.push_back((0, 0, 1));
    visited[0][0] = true;

    while let Some((row, col, steps)) = queue.pop_front() {
        for d in 0..4 {
            let nr = row + dx[d];
            let nc = col + dy[d];

            if nr == 70 && nc == 70 {
                print!("{steps}");
                return;
            }

            if !(0..71).contains(&nr) || !(0..71).contains(&nc) { continue; }
            if visited[nr as usize][nc as usize] || grid[nr as usize][nc as usize] == '#' { continue; }


            visited[nr as usize][nc as usize] = true;
            queue.push_back((nr, nc, steps + 1));
        }
    }
}

