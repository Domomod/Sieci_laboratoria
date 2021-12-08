#pragma once
#include "tree.hh"
#include "CTrieNode.hpp"
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

    int insert_add(const std::vector<int> &oid, const CTrieNode &node);
    tree<CTrieNode>::iterator find_name(std::string name);
    tree<CTrieNode>::iterator find_oid(int oid_n);

};