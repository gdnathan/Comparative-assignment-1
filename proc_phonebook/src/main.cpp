#include "phonebook.hpp"
#include "repl.hpp"

#include <iostream>

void debug(NTree &ntree);
void debug(NTree &ntree) {
    std::cout << "elem: " << ntree.elem << std::endl;
    std::cout << "leaf: " << (ntree.leaf == nullptr ? "nullptr" : ntree.leaf->name) << std::endl;

    for (auto &child : ntree.childrens) {
        std::cout << "childrens: " << std::endl;
        debug(*child);
    }
}

void print_help()
{
    std::cout << "Available commands:" << std::endl;
    std::cout << "exit: exit the application" << std::endl;
    std::cout << "help: print this help message" << std::endl;
    std::cout << "new <name> <address> <number>: add a new entry" << std::endl;
    std::cout << "search <name>: search for an entry, by either its name or number" << std::endl;
    std::cout << "delete <name>: delete an entry, by either its name or number" << std::endl;
    std::cout << "clear: clear the terminal" << std::endl << std::endl;
}

int main()
{
    Phonebook phonebook = Phonebook{.by_name = NTree{.elem = ' ', .childrens = {}, .leaf = nullptr},
                                    .by_number = NTree{.elem = ' ', .childrens = {}, .leaf = nullptr}};

    init_repl();
    while (true) {
        Args args = get_input();
        switch (args.input) {
            case Input::EXIT:
                return 0;
            case Input::HELP:
                print_help();
                break;
            case Input::CLEAR:
                std::cout << "\x1B[2J\x1B[1;1H" << std::endl;
                break;
            case Input::ADD:
                if (args.datas.size() != 3) {
                    std::cout << "Invalid number of arguments" << std::endl;
                    break;
                }
                add_node(phonebook.by_name, args.datas[0],
                         std::make_unique<Data>(
                             Data{.name = args.datas[0], .address = args.datas[1], .number = args.datas[2]}));
                add_node(phonebook.by_number, args.datas[2],
                         std::make_unique<Data>(
                             Data{.name = args.datas[0], .address = args.datas[1], .number = args.datas[2]}));
                std::cout << "New entry:\nName: " << args.datas[0] << std::endl;
                std::cout << "Address: " << args.datas[1] << std::endl;
                std::cout << "Number: " << args.datas[2] << std::endl;
                break;
            case Input::SEARCH:
                if (args.datas.size() != 1) {
                    std::cout << "Invalid number of arguments" << std::endl;
                    break;
                }
                if (args.datas[0][0] < '9' && args.datas[0][0] > '0') {
                    auto data = search_node(phonebook.by_number, args.datas[0]);
                    if (data == nullptr) {
                        std::cout << "No entry found for " << args.datas[0] << std::endl;
                        break;
                    }
                    std::cout << "Found:\nName: " << data->name << std::endl;
                    std::cout << "Address: " << data->address << std::endl;
                    std::cout << "Number: " << data->number << std::endl;
                } else {
                    auto data = search_node(phonebook.by_name, args.datas[0]);
                    if (data == nullptr) {
                        std::cout << "No entry found for " << args.datas[0] << std::endl;
                        break;
                    }
                    std::cout << "Name: " << data->name << std::endl;
                    std::cout << "Address: " << data->address << std::endl;
                    std::cout << "Number: " << data->number << std::endl;
                }
                break;
            case Input::DELETE:
                if (args.datas.size() != 1) {
                    std::cout << "Invalid number of arguments" << std::endl;
                    break;
                }
                delete_node(phonebook.by_name, args.datas[0]);
                delete_node(phonebook.by_number, args.datas[0]);
                break;
            case Input::UNKNOWN:
                std::cout << "Unknown command" << std::endl;
                break;
        }
        // std::cout << "BY NAME ---------" << std::endl;
        // debug(phonebook.by_name);
        // std::cout << "BY NBR ---------" << std::endl;
        // debug(phonebook.by_number);
    }
}
