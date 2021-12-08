#include "../include/CMIBTree.hpp"
#include "CTrieNode.hpp"

int CMIBTree ::insert_add(const std::vector<int> &oid, const CTrieNode &node)
{
    auto node_it = head;
    int depth = 0;

    std::cout << node_it->get_name() << "\n";
    for (auto i : oid)
    {
        node_it++;
        while (i > 1)
        {
            node_it = node_it.next_skip_children();
            i--;
        }

        std::cout << node_it->get_name() << "\n";
    }

    tree_mib.append_child(node_it, node);
    std::cout << "---------------------\n";

    return 0;
}

tree<CTrieNode>::iterator CMIBTree ::find_name(std::string name)
{
    auto find_iter = oid_map.find(name); 

return find_iter;
}

tree<CTrieNode>::iterator CMIBTree ::find_oid(int oid_n)
{
    auto find_iter = oid_map.find(oid_n); 
    return find_iter;
}

CMIBTree ::CMIBTree() : head(tree_mib.set_head(CTrieNode("mib", 1)))
{
}