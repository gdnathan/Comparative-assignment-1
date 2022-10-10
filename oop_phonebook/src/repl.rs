// pub mod repl;
pub use crate::*;

use std::io::Write;

pub enum Input {
    Exit,
    Help,
    Clear,
    New {
        name: String,
        address: String,
        number: String,
    },
    Search {
        search_string: String,
    },
    Delete {
        search_string: String,
    },
}

pub fn init_repl() {
    print!("{}[2J", 27 as char);
    print!("\x1B[2J\x1B[1;1H");
    println!("Welcome to your best phonebook application !");
    println!("Type 'help' to get a list of available commands.");
}

pub fn get_input() -> Input {
    loop {
        print!("> ");
        std::io::stdout().lock().flush().unwrap();
        let mut input = String::new();
        std::io::stdin().read_line(&mut input).unwrap();
        if input.is_empty() {
            return Input::Exit;
        }
        let mut input = input.split_whitespace();
        match input.next() {
            Some("exit") => return Input::Exit,
            Some("help") => return Input::Help,
            Some("clear") => return Input::Clear,
            Some("new") => {
                let name = input.next();
                let mut address: String = String::new();
                #[allow(unused_assignments)]
                let mut number: String = String::new();

                let mut tmp: String = String::new();
                loop {
                    let new = input.next();
                    if new.is_none() {
                        number = tmp;
                        break;
                    }
                    if !tmp.is_empty() {
                        address.push_str(&tmp.clone());
                        address.push(' ');
                    }
                    tmp = new.unwrap().to_string();
                }
                if name.is_none()
                    && address.is_empty()
                    && number.is_empty()
                    && name.unwrap().chars().nth(0).unwrap().is_numeric()
                {
                    println!("Invalid input");
                    continue;
                }
                return Input::New {
                    name: name.unwrap().to_string(),
                    address,
                    number,
                };
            }
            Some("search") => {
                let search_string = input.next();
                if search_string.is_none() {
                    println!("Invalid input");
                    continue;
                }
                return Input::Search {
                    search_string: search_string.unwrap().to_string(),
                };
            }
            Some("delete") => {
                let search_string = input.next();
                if search_string.is_none() {
                    println!("Invalid input");
                    continue;
                }
                return Input::Delete {
                    search_string: search_string.unwrap().to_string(),
                };
            }
            _ => {
                println!("Invalid input");
                continue;
            }
        };
    }
}
