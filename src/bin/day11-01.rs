use std::{collections::HashMap, fs::File, io::{BufReader, Read}, mem};

fn sim(map: &mut HashMap<i64, i64>, blinks: &i32) {
    let mut new_map: HashMap<i64, i64> = HashMap::new();

    for _ in 0..*blinks {
        for (key, val) in &mut *map {
            if *key == 0 { *new_map.entry(1).or_insert(0) += *val; continue; }

            let stone_str = key.to_string();

            let len = stone_str.len();

            if len % 2 == 0 {
                let (left, right) = stone_str.split_at(len / 2);

                *new_map.entry(left.parse::<i64>().unwrap()).or_insert(0) += *val;
                *new_map.entry(right.parse::<i64>().unwrap()).or_insert(0) += *val;
            }

            else {
                *new_map.entry(*key * 2024).or_insert(0) += *val;
            }
        }
        mem::swap(map, &mut new_map);
        new_map.clear();
    }
}

fn main() {
    let mut reader = BufReader::new(File::open("data.txt").unwrap());

    let mut line: String = String::new();

    let _ = reader.read_to_string(&mut line).unwrap();

    let mut map: HashMap<i64, i64> = HashMap::new();

    for elem in line.split(' ') {
        *map.entry(elem.parse::<i64>().unwrap()).or_insert(0) += 1;
    }

    let blinks = 25;

    sim(&mut map, &blinks);

    print!("{}", map.into_values().sum::<i64>());
}