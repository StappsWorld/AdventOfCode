use num_bigint::BigUint;
use num_traits::{Zero, One};
use std::fs::File;
use std::io::{BufReader, Read};

const TABLE_SIZE : usize = 9;
const DAYS : usize = 65000;

fn next_day(table : &mut Vec<BigUint>) {
    let mut new_table : Vec<BigUint> = vec![Zero::zero(); TABLE_SIZE];

    new_table[8] += &table[0];
    new_table[6] += &table[0];
    for i in 1..TABLE_SIZE {
        new_table[i - 1] += &table[i];
    }

    for i in 0..TABLE_SIZE {
        table[i] = new_table[i].clone();
    }
}

fn count_fish(table : &Vec<BigUint>) -> BigUint {
    let mut total = Zero::zero();

    for i in 0..TABLE_SIZE {
        total += &table[i];
    }

    total
}

fn print_table(table : &Vec<BigUint>) {
    print!("{{");
    for i in 0..TABLE_SIZE {
        print!("{}", table[i]);
        if i != TABLE_SIZE - 1 {
            print!(", ");
        }
    }
    println!("}} => Total Fish: {}", count_fish(table));
}

fn main() -> std::io::Result<()> {
    let mut fp = File::open("input.txt")?;
    let mut buf_reader = BufReader::new(fp);
    let mut contents = String::new();

    let mut table : Vec<BigUint> = vec![Zero::zero(); TABLE_SIZE];

    buf_reader.read_to_string(&mut contents)?;

    for c in contents.split(',') {
        // println!("{}", c);
        let i = match c.trim().parse::<usize>() {
            Ok(i) => i,
            Err(_) => {
                println!("Failed to parse {}", c);
                continue
            },
        };
        assert!(i >= 1 && i <= 8);

        table[i] += &One::one();
    }

    /*print_table(&table)*/;
    for i in 0..DAYS {
        next_day(&mut table);
        if i % 1000 == 0 {
            println!("{} => Total: {}", i, count_fish(&table));
        }
        /*print_table(&table)*/;
    }

    println!("Final total: {}", count_fish(&table));

    Ok(())
}