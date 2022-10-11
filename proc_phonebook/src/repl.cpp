#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "repl.hpp"

void init_repl()
{
    std::cout << "\x1B[2J\x1B[1;1H" << std::endl;
    std::cout << "Welcome to your best phonebook application !" << std::endl;
    std::cout << "Type 'help' to get a list of available commands."
              << std::endl;
}

std::vector<std::string> split(const std::string& s)
{
    std::vector<std::string> v;
    std::istringstream iss(s);
    std::string temp;
    while (iss >> temp)
        v.push_back(temp);
    return v;
}

Args get_input()
{
    std::string input;
    Args args = Args{.input = UNKNOWN, .datas = {}};
    std::cout << "> ";
    std::getline(std::cin, input);
    if (input.empty()) {
        args.input = EXIT;
        return args;
    }
    auto datas = split(input);

    auto it = datas.begin();

    std::string f = *it++;
    if (f == "exit")
        args.input = EXIT;
    else if (f == "help")
        args.input = HELP;
    else if (f == "clear")
        args.input = CLEAR;
    else if (f == "new") {
        args.input = ADD;
        std::string name = *it++;
        std::string address = "";
        std::string number = "";
        std::string tmp = "";
        while (true) {
            auto a = it++;
            if (a == datas.end()) {
                number = tmp;
                break;
            }
            if (!tmp.empty()) {
                address += tmp;
                address += " ";
            }
            tmp = *a;
        }
        if (name.empty() || address.empty() || number.empty()) {
            args.input = UNKNOWN;
            return args;
        }
        args.datas.push_back(name);
        args.datas.push_back(address);
        args.datas.push_back(number);
    } else if (f == "search") {
        auto str = *it++;
        if (str.empty()) {
            args.input = UNKNOWN;
            return args;
        }
        args.datas.push_back(str);
        args.input = SEARCH;
    } else if (f == "delete") {
        auto str = *it++;
        if (str.empty()) {
            args.input = UNKNOWN;
            return args;
        }
        args.datas.push_back(str);
        args.input = DELETE;
    } else {
        args.input = UNKNOWN;
    }
    return args;
}


