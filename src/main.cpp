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
    printf("start seq\n");
   // fileSequencer.initialize("../data/RFC1213-MIB.mib");
    //fileSequencer.initialize("data/SNMPv2-SMI.mib");

   CMIBTree cmibTree;

 /*   cmibTree.insert_add(CTrieNode("mib-2", 0,"parent"));
    cmibTree.insert_add(CTrieNode("system", 3,"mib-2"));
    cmibTree.insert_add(CTrieNode("HCI", 98,"system"));
    cmibTree.insert_by_name("HCI",CTrieNode("interfaces1", 1,"HCI"));
    cmibTree.insert_by_name("HCI",CTrieNode("interfaces2", 2,"HCI"));
    cmibTree.insert_by_name("HCI",CTrieNode("interfaces3", 3,"HCI")); */

    //--------------------------

    cmibTree.insert_by_oid({1,3,6,1,2,1},CTrieNode("system", 1,"Root-Node"));
    cmibTree.insert_by_oid({1,3,6,1,2,1},CTrieNode("interfaces", 2,"parent_name"));
    cmibTree.insert_by_oid({1,3,6,1,2,1},CTrieNode("at", 3,"Root-Node"));
    cmibTree.insert_by_oid({1,3,6,1,2,1},CTrieNode("ip", 4,"parent_name"));
    cmibTree.insert_by_oid({1,3,6,1,2,1},CTrieNode("icmp", 5,"Root-Node"));
    cmibTree.insert_by_oid({1,3,6,1,2,1},CTrieNode("tcp", 6,"parent_name"));
    cmibTree.insert_by_oid({1,3,6,1,2,1},CTrieNode("udp", 7,"Root-Node"));
    cmibTree.insert_by_oid({1,3,6,1,2,1},CTrieNode("egp", 8,"parent_name"));
    cmibTree.insert_by_oid({1,3,6,1,2,1},CTrieNode("dummy-name", 9,"Root-Node"));
    cmibTree.insert_by_oid({1,3,6,1,2,1},CTrieNode("transmission", 10,"parent_name"));
    cmibTree.insert_by_oid({1,3,6,1,2,1},CTrieNode("snmp", 11,"Root-Node"));

    cmibTree.find_oid2({1,3,6,1,2,1});
    cmibTree.find_oid2({1,3,6,1,2,1,1});
    cmibTree.find_oid2({1,3,6,1,2,1,2});
    cmibTree.find_oid2({1,3,6,1,2,1,3});
    cmibTree.find_oid2({1,3,6,1,2,1,4});
   // cmibTree.insert_by_oid({1,3,6,1,2,1},CTrieNode("dd", 1,"iso"));
  //  cmibTree.insert_by_oid({1,3,6,1,2,1},CTrieNode("dd", 2,"iso"));
  //  cmibTree.insert_by_oid({1,3,6,1,2,1},CTrieNode("org", 3,"iso"));
    //cmibTree.find_oid2({});
   // cmibTree.insert_by_oid({6},CTrieNode("dod", 6,"org"));


  /*  cmibTree.insert_by_oid({},CTrieNode("mib-2", 0,"OSI"));
    cmibTree.insert_by_oid({1},CTrieNode("interfaces1", 1,"mib-2"));
    cmibTree.insert_by_oid({1},CTrieNode("interfaces2", 2,"mib-2"));
    cmibTree.insert_by_oid({1,1},CTrieNode("interfaces3", 3,"mib-2"));
    cmibTree.find_name("interfaces1");
    cmibTree.find_name("interfaces2");
    cmibTree.find_name("interfaces3");
 //   cmibTree.find_oid(1);
   /* cmibTree.insert_add({}, CTrieNode("interfaces", 2));
    cmibTree.insert_add({1}, CTrieNode("HCI", 2));
    cmibTree.insert_add({1, 1}, CTrieNode("mouse", 2));
    cmibTree.insert_add({}, CTrieNode("adresses", 3)); */
    //auto itr = cmibTree.find_name("HCI");

}