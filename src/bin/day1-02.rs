use std::fs::File;
use std::io::{BufRead, BufReader};
use std::collections::HashMap;

fn main() {
    let reader = BufReader::new(File::open("data.txt").unwrap());

    let mut v1: Vec<i32> = Vec::new();
    let mut v2: HashMap<i32, i32> = HashMap::new();

    for line in reader.lines(){
        let line = line.unwrap();

        let Ok((num1, num2)) = sscanf::sscanf!(line, "{}   {}", i32, i32) else { panic!("invalid") };

        v1.push(num1); 
        *v2.entry(num2).or_insert(0) += 1;
    }

    let mut ans = 0;

    for elem in v1 {
        ans += elem * v2.get(&elem).unwrap_or(&0);
    }

    print!("{ans}");
}