#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <regex>
#include <algorithm>

#include "cmib_tree.hpp"
#include "cmib_sequencer.hpp"
#include "serialization/cber_coder.hpp"



int main(int, char **)
{
    CberCoder coder;
    coder.encodeInteger(std::numeric_limits<uint8_t>::max(), visibility_t::UNIVERSAL, PC_t::PRIMITIVE, 10);
    coder.encodeInteger(std::numeric_limits<uint16_t>::max(), visibility_t::UNIVERSAL, PC_t::PRIMITIVE, 31);
    coder.encodeInteger(std::numeric_limits<uint32_t>::max(), visibility_t::UNIVERSAL, PC_t::PRIMITIVE, 255);
    coder.encodeInteger(std::numeric_limits<uint64_t>::max(), visibility_t::UNIVERSAL, PC_t::PRIMITIVE, 1024);


    // CmibFileSequencer fileSequencer;
    // fileSequencer.initialize("data/RFC1213-MIB.mib");
    //fileSequencer.initialize("data/SNMPv2-SMI.mib");

    // CMIBTree cmibTree;
    // cmibTree.insert_add({}, CTrieNode("system", 1));
    // cmibTree.insert_add({}, CTrieNode("interfaces", 2));
    // cmibTree.insert_add({1}, CTrieNode("HCI", 2));
    // cmibTree.insert_add({1, 1}, CTrieNode("mouse", 2));
    // cmibTree.insert_add({}, CTrieNode("adresses", 3));
}