use std::collections::{HashSet, VecDeque};
use std::io::{BufRead, BufReader};
use std::fs::File;

fn bfs(wall: &(i32, i32), walls: &mut HashSet<(i32, i32)>, path: &mut HashSet<(i32, i32)>) -> Option<(i32, i32)> {
    walls.insert(*wall);

    if !path.is_empty() && !path.contains(wall) { return None; }

    let mut new_path: HashSet<(i32, i32)> = HashSet::new();
    const DX: [i32; 4] = [1, 0, -1, 0];
    const DY: [i32; 4] = [0, -1, 0, 1];

    let mut queue: VecDeque<(i32, i32)> = VecDeque::new();
    let mut visited: HashSet<(i32, i32)> = HashSet::new();

    queue.push_back((0, 0));
    visited.insert((0, 0));
    new_path.insert((0, 0));

    while let Some((x, y)) = queue.pop_front() {
        for d in 0..4 {
            let nx = x + DX[d];
            let ny = y + DY[d];

            if !(0..71).contains(&nx) || !(0..71).contains(&ny) {
                continue;
            }

            if walls.contains(&(nx, ny)) || visited.contains(&(nx, ny)) {
                continue;
            }

            queue.push_back((nx, ny));
            visited.insert((nx, ny));
            new_path.insert((nx, ny));
        }
    }

    if !visited.contains(&(70, 70)) {
        *path = new_path;
        return Some(*wall);
    }

    None
}

fn main() {
    let reader = BufReader::new(File::open("data.txt").unwrap());
    let mut walls: HashSet<(i32, i32)> = HashSet::new();
    let mut path: HashSet<(i32, i32)> = HashSet::new();

    for line in reader.lines() {
        let line = line.unwrap();
        if let Ok((x, y)) = sscanf::scanf!(&line.as_str(), "{},{}", i32, i32) {
            if let Some(point) = bfs(&(x, y), &mut walls, &mut path) {
                print!("{},{}", point.0, point.1);
                return;
            }
        }
    }
}