use std::{collections::{HashMap, HashSet}, fs::File, io::{BufRead, BufReader}};
use std::ops::{Add, Sub};

#[derive(Copy, Clone, Hash, PartialEq, Eq)]
struct Point {
    x: i32,
    y: i32
}

impl Add for Point {
    type Output = Self;

    fn add(self, other: Self) -> Self {
        Self {
            x: self.x + other.x,
            y: self.y + other.y,
        }
    }
}

impl Sub for Point {
    type Output = Self;

    fn sub(self, other: Self) -> Self {
        Self {
            x: self.x - other.x,
            y: self.y - other.y,
        }
    }
}

fn main() {
    let mut antenna_coords: HashMap<char, Vec<Point>> = HashMap::new();
    let mut unique_nodes: HashSet<Point> = HashSet::new();

    let mut rows: i32 = 0; let mut cols: usize = 0;

    let reader = BufReader::new(File::open("data.txt").unwrap());
    
    for line in reader.lines() {
        let line = line.unwrap();
        cols = line.len();

        for col in 0..line.len() {  
            let ch = line.chars().nth(col).unwrap();
            if ch != '.' { antenna_coords.entry(ch).or_default().push(Point { x: rows, y: col as i32 }); } 
        }
        rows += 1;
    }

    for (_, coords) in &antenna_coords {
        for i in 0..coords.len() - 1 {
            for j in i + 1..coords.len() {
                let delta = coords[j] - coords[i];

                let mut p1 = coords[i] - delta;
                let mut p2 = coords[j] + delta;

                while p1.x >= 0 && p1.x < rows && p1.y >= 0 && p1.y < cols as i32 {
                    unique_nodes.insert(p1);
                    p1 = p1 - delta;
                }


                while p2.x >= 0 && p2.x < rows && p2.y >= 0 && p2.y < cols as i32 {
                    unique_nodes.insert(p2);
                    p2 = p2 + delta;
                }
            }
        }
    }

    for (_, coords) in &antenna_coords {
        if coords.len() >= 2 {
            for coord in coords { unique_nodes.insert(*coord); }
        }
    }

    print!("{}", unique_nodes.len());
}