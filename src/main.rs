use std::{env, process};
use x::parse_operations;

fn main() {
    let operations = match parse_operations(env::args().skip(1)) {
        Ok(operations) => operations,
        Err(e) => {
            eprintln!("error while parsing operations: {}", e);
            process::exit(1);
        }
    };

    for operation in operations {
        match operation.execute() {
            Ok(_) => {}
            Err(e) => {
                eprintln!("error while executing operation: {}", e);
                process::exit(1);
            }
        }
    }
}
