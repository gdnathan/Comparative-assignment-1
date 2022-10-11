#include "phonebook.hpp"
#include <iostream>
#include <memory>

std::unique_ptr<NTree> create_node() noexcept
{
    return std::make_unique<NTree>(NTree{.elem = ' ', .childrens = {}, .leaf = nullptr});
}

int add_node(NTree& node, const std::string& str, std::unique_ptr<Data> data)
{
    if (str.empty())
        return 1;

    NTree* current = &node;

    bool find = false;
    for (char c: str) {
        for (auto& child: current->childrens) {
            if (child->elem == c) {
                find = true;
                current = child.get();
            }
        }
        if (!find) {
            auto new_node = create_node();
            new_node->elem = c;
            current->childrens.push_back(std::move(new_node));
            current = current->childrens.back().get();
        }
    }
    current->leaf = std::move(data);
    return 0;
}

Data* search_node(NTree& node, const std::string& str)
{
    if (str.empty())
        return nullptr;

    NTree* current = &node;

    for (char c: str) {
        for (auto& child: current->childrens) {
            if (child->elem == c) {
                current = child.get();
            }
        }
    }
    if (current->leaf == nullptr)
        return nullptr;
    return &*current->leaf;
}

void delete_node(NTree& node, const std::string& str)
{
    if (str.empty())
        return;

    NTree* current = &node;

    for (char c: str) {
        if (c < 'a' || c > 'z')
            return;
        for (auto& child: current->childrens) {
            if (child->elem == c) {
                current = child.get();
            }
        }
    }
    current->leaf = nullptr;
}
