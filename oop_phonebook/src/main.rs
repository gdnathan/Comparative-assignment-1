pub mod phonebook;
pub mod repl;

pub use phonebook::*;
pub use repl::*;

fn main() {
    let mut phonebook = Phonebook::new();

    repl::init_repl();

    loop {
        match repl::get_input() {
            Input::Exit => break,
            Input::Help => print_help(),
            Input::Clear => init_repl(),
            Input::New {
                name,
                address,
                number,
            } => {
                phonebook.add(name.clone(), address.clone(), number.clone());
                println!("New entry:\nname: {}\naddress: {}\nnumber: {}", name, address, number);
            }
            Input::Search{ search_string } => {
                if let Some(data) = phonebook.search(search_string.clone()) {
                    println!("Found:\nname: {}\naddress: {}\nnumber: {}", data.name, data.address, data.phone);
                } else {
                    println!("No entry found for {}", search_string);
                }
            }
            Input::Delete { search_string } => {
                phonebook.delete(search_string.clone())
            }
        }
    }
    print!("{}[2J", 27 as char);
    print!("\x1B[2J\x1B[1;1H");
}

fn print_help() {
    println!("Available commands:");
    println!("exit: exit the program");
    println!("help: print this help");
    println!("new <name> <address> <number>: add a new entry");
    println!("search <name>: search for an entry, by either its name or number");
    println!("delete <name>: delete an entry, by either its name or number\n");
    println!("clear: clear the terminal");
}
