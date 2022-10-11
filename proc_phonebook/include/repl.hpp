#pragma once

#include <string>
#include <vector>

enum Input
{
    EXIT,
    HELP,
    ADD,
    SEARCH,
    DELETE,
    CLEAR,
    UNKNOWN
};

struct Args
{
    Input input;
    std::vector<std::string> datas;
};

void init_repl();
Args get_input();
