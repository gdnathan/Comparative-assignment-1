#pragma once

#include <memory>
#include <string>
#include <vector>
#include <optional>

struct Data
{
    std::string name;
    std::string address;
    std::string number;
};

struct NTree
{
    char elem;
    std::vector<std::unique_ptr<struct NTree>> childrens;
    std::unique_ptr<Data> leaf;
};

struct Phonebook
{
    NTree by_name;
    NTree by_number;
};

int add_node(NTree& node, const std::string& str, std::unique_ptr<Data> data);
Data *search_node(NTree& node, const std::string& str);
void delete_node(NTree& node, const std::string& str);
