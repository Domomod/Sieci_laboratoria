#pragma once
#include "tree.hh"
#include "ctree_node.hpp"
#include <iostream>
#include <vector>
#include <map>

class CMIBTree
{

private:
    tree<CTrieNode> tree_mib;
    const tree<CTrieNode>::iterator head;
    std::map<std::string, std::vector<int>> oid_map;

public:
    CMIBTree();
    tree<CTrieNode>::iterator find_name(std::string name);
    tree<CTrieNode>::iterator find_oid(int oid_n);
    int insert_by_name(const std::string &name, const CTrieNode &node);

    tree<CTrieNode>::iterator find_oid2(const std::vector<int> &oid);
    int insert_by_oid(const std::vector<int> &oid, const CTrieNode &node);


    int insert_add(CTrieNode node);
};