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
    coder.encodeInteger(std::numeric_limits<uint8_t>::max(),  visibility_t::UNIVERSAL, PC_t::PRIMITIVE);
    coder.encodeInteger(std::numeric_limits<uint16_t>::max(), visibility_t::UNIVERSAL, PC_t::PRIMITIVE);
    coder.encodeInteger(std::numeric_limits<uint32_t>::max(), visibility_t::UNIVERSAL, PC_t::PRIMITIVE);
    coder.encodeInteger(std::numeric_limits<uint64_t>::max(), visibility_t::UNIVERSAL, PC_t::PRIMITIVE);
    coder.encodeBool(false, visibility_t::UNIVERSAL, PC_t::PRIMITIVE);
    coder.encodeBool(true, visibility_t::UNIVERSAL, PC_t::PRIMITIVE);
    coder.encodeOctetString("BADDCAFE", visibility_t::UNIVERSAL, PC_t::PRIMITIVE);
    coder.encodeOctetString("DEADBEEF", visibility_t::UNIVERSAL, PC_t::PRIMITIVE);
    coder.encodeNull(visibility_t::UNIVERSAL, PC_t::PRIMITIVE);

    printf("Encoding tags:\n");
    cber_identifier i1 = coder.encodeIdentifier( visibility_t::UNIVERSAL, PC_t::PRIMITIVE, 10 );
    cber_identifier i2 = coder.encodeIdentifier( visibility_t::UNIVERSAL, PC_t::PRIMITIVE, 31);
    cber_identifier i3 = coder.encodeIdentifier( visibility_t::UNIVERSAL, PC_t::PRIMITIVE, 255);
    cber_identifier i4 = coder.encodeIdentifier( visibility_t::UNIVERSAL, PC_t::PRIMITIVE, 1024);
    coder.print_identifier_bin(i1); printf("\n");
    coder.print_identifier_bin(i2); printf("\n");
    coder.print_identifier_bin(i3); printf("\n");
    coder.print_identifier_bin(i3); printf("\n");


    printf("Encoding lengths:\n");
    cber_length l1 = coder.encodeLength(std::numeric_limits<uint8_t>::max() );
    cber_length l2 = coder.encodeLength(std::numeric_limits<uint16_t>::max());
    cber_length l3 = coder.encodeLength(std::numeric_limits<uint32_t>::max());
    coder.print_length_bin(l1); printf("\n");
    coder.print_length_bin(l2); printf("\n");
    coder.print_length_bin(l3); printf("\n");

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