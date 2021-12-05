#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <regex>
#include <algorithm>

#include "cmib_tree.hpp"
#include "cmib_sequencer.hpp"

int main(int, char **)
{
    std::ifstream t("data/RFC1213-modified.mib");
    std::string str((std::istreambuf_iterator<char>(t)),
                     std::istreambuf_iterator<char>());

    CmibFileSequencer::parse_all(str);

    CMIBTree cmibTree;
    cmibTree.insert_add({}, CTrieNode("system", 1));
    cmibTree.insert_add({}, CTrieNode("interfaces", 2));
    cmibTree.insert_add({1}, CTrieNode("HCI", 2));
    cmibTree.insert_add({1, 1}, CTrieNode("mouse", 2));
    cmibTree.insert_add({}, CTrieNode("adresses", 3));
}