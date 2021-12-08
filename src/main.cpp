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
    CmibFileSequencer fileSequencer;
    fileSequencer.initialize("data/RFC1213-MIB.mib");
    //fileSequencer.initialize("data/SNMPv2-SMI.mib");

    CMIBTree cmibTree;
    cmibTree.insert_add({}, CTrieNode("system", 1));
    cmibTree.insert_add({}, CTrieNode("interfaces", 2));
    cmibTree.insert_add({1}, CTrieNode("HCI", 2));
    cmibTree.insert_add({1, 1}, CTrieNode("mouse", 2));
    cmibTree.insert_add({}, CTrieNode("adresses", 3));
}