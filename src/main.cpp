#include <iostream>
#include <vector>
#include <map>
#include "CMIBTree.hpp"

int main(int, char **)
{
    CMIBTree cmibTree;
    cmibTree.insert_add({}, CTrieNode("system", 1));
    cmibTree.insert_add({}, CTrieNode("interfaces", 2));
    cmibTree.insert_add({1}, CTrieNode("HCI", 2));
    cmibTree.insert_add({1, 1}, CTrieNode("mouse", 2));
    cmibTree.insert_add({}, CTrieNode("adresses", 3));
     

}