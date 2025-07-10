use std::fs::File;
use std::io::{BufRead, BufReader};
use std::iter::zip;

fn main() {
    let reader = BufReader::new(File::open("data.txt").unwrap());

    let mut v1: Vec<i32> = Vec::new();
    let mut v2: Vec<i32> = Vec::new();

    for line in reader.lines(){
        let line = line.unwrap();

        let Ok((num1, num2)) = sscanf::sscanf!(line, "{}   {}", i32, i32) else { panic!("invalid") };

        v1.push(num1); v2.push(num2);
    }
    
    v1.sort(); v2.sort();

    let mut ans = 0;

    for (a, b) in zip(v1, v2) {
        ans += (a - b).abs();
    }

    print!("{ans}");
}