use std::{collections::{HashSet, VecDeque}, fs::File, io::{BufRead, BufReader}};


#[derive(Hash, PartialEq, Eq)]
struct State {
    x: i32,
    y: i32,
    height: i32,
}

fn main() {
    let reader = BufReader::new(File::open("data.txt").unwrap());

    let mut starting_points: Vec<(i32, i32)> = Vec::new();
    let mut grid: Vec<Vec<i32>> = Vec::new();

    let mut rows = 0;

    for line in reader.lines() {
        let line = line.unwrap();

        for cols in 0..line.len() {
            if line.chars().nth(cols).unwrap() == '0' { starting_points.push((rows, cols as i32)); }
        }

        let row: Vec<i32> = line.chars().map(|x| x.to_digit(10).unwrap() as i32).collect();
        grid.push(row);

        rows += 1;
    }

    let cols = grid[0].len() as i32;

    let dx = [1, 0, 0, -1];
    let dy = [0, 1, -1, 0];

    let mut total_paths = 0;

    for (sx, sy) in starting_points {
        let mut q: VecDeque<State> = VecDeque::new();
        let mut visited: HashSet<State> = HashSet::new();

        let mut trails = 0;

        q.push_back( State{ x: sx, y: sy, height: 0 } );
        visited.insert( State{ x: sx, y: sy, height: 0 } );

        while !q.is_empty() {
            if let Some(State { x, y, height: prev_height }) = q.pop_front() {
                if prev_height == 9 { trails += 1; continue; }

                for d in 0..4 {
                    let nx = x + dx[d];
                    let ny = y + dy[d];

                    if nx < 0 || nx >= rows || ny < 0 || ny >= cols { continue; }

                    let curr_height = grid[nx as usize][ny as usize];
                    if visited.contains(&State{ x: nx, y: ny, height: curr_height }) { continue; }

                    if curr_height - prev_height == 1 {
                        q.push_back(State { x: nx, y: ny, height: curr_height });
                        visited.insert(State { x: nx, y: ny, height: curr_height });
                    }
                }
            } 
        }
        total_paths += trails;
    }
    print!("{total_paths}");
}
