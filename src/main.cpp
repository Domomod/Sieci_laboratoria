#include <iostream>
#include <vector>
#include <map>
#include "CMIBTree.hpp"

int main(int, char **)
{
    CMIBTree cmibTree;
    cmibTree.insert_add({}, CTrieNode("system", 1));
    cmibTree.insert_add({}, CTrieNode("interfaces", 2));
    cmibTree.insert_add({1}, CTrieNode("dupa", 2));
    cmibTree.insert_add({1, 1}, CTrieNode("DUUPA", 2));
    cmibTree.insert_add({}, CTrieNode("kupa", 3));

    //BEGIN TREE

    /* CTrieNode mib_n, system_n, interfaces_n, at_n, ip_n, icmp_n, tcp_n, udp_n, egp_n;
    mib_n.init(1, "mib");
    system_n.init(1, "system");
    interfaces_n.init(2, "interfaces");
    at_n.init(3, "at");
    ip_n.init(4, "ip");
    icmp_n.init(5, "icmp");
    tcp_n.init(6, "tcp");
    udp_n.init(7, "udp");
    egp_n.init(8, "egp");
    tree<CTrieNode>::iterator mib_it, it2;
    mib_it = tree_mib.set_head(mib_n);
    tree_mib.append_child(mib_it, system_n);
    it2 = tree_mib.append_child(mib_it, interfaces_n);

    //tree_mib.append_child()
    CTrieNode test = *mib_it;
    CTrieNode test2 = *++mib_it;
    tree_mib.append_child(it2, icmp_n);
    CTrieNode test3 = *++mib_it;
    CTrieNode test4 = *++it2;
    std::cout << test.get_name() + "\r\n";
    std::cout << test2.get_name() + "\r\n";
    std::cout << test3.get_name() + "\r\n";
    std::cout << test4.get_name() + "\r\n"; 
    // int oid_t;
    //  std::string name_t;
    //  put_in_tree(oid_t,name_t);

    //CTrieNode node_child_TEST;
    //node_child_TEST.ACCESS = "string_test";
    //node_child=tree_root_it.insert(node_root,node_child_TEST);
    //  tree<CTrieNode>::iterator its = tree_root_it.begin();
    // CTrieNode test = *its;
    //std::cout << test.get_ACCESS();
    //node.ACCESS = "ll"; */
}