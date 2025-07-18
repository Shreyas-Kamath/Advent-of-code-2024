use std::{collections::{HashMap, VecDeque}, fs::File, io::{BufRead, BufReader}};

struct Instruction {
    lhs: String,
    op: String,
    rhs: String,
    result: String
}

fn main() {
    let reader = BufReader::new(File::open("regs.txt").unwrap());

    let mut q: VecDeque<Instruction> = VecDeque::new();

    let mut registers: HashMap<String, i32> = HashMap::new();

    for line in reader.lines() {
        let line = line.unwrap();

        if let Some((key, val)) = line.split_once(": ") {
            registers.insert(key.to_string(), val.parse::<i32>().unwrap());
        }
    }

    let reader = BufReader::new(File::open("data.txt").unwrap());

    for line in reader.lines() {
        let line = line.unwrap();

        if let Ok((lhs, op, rhs, result)) = sscanf::sscanf!(line, "{} {} {} -> {}", String, String, String, String) {
            q.push_back(Instruction { lhs, op, rhs, result });
        }
    }

    while !q.is_empty() {
        let front = q.pop_front().unwrap();

        if registers.contains_key(&front.lhs) && registers.contains_key(&front.rhs) {
            match front.op.as_str() {
                "AND" => registers.insert(front.result, registers[&front.lhs] & registers[&front.rhs]),

                "OR" => registers.insert(front.result, registers[&front.lhs] | registers[&front.rhs]),

                _ => registers.insert(front.result, registers[&front.lhs] ^ registers[&front.rhs])
            };
        }

        else { q.push_back(front); }
    }

    let mut vec: Vec<(String, i32)> = registers
    .iter()
    .filter(|(k, _v)| k.starts_with('z'))
    .map(|(k, v)| (k.clone(), *v))
    .collect();

    vec.sort_by(|lhs, rhs| rhs.0.cmp(&lhs.0));
    
    let result: String = vec
    .iter()
    .map(|(_, v)| if *v == 1 { '1' } else { '0' })
    .collect();

    println!("{}", i64::from_str_radix(&result, 2).unwrap());
}