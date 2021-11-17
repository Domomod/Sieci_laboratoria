#include "cmib_tree.hpp"

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

CMIBTree ::CMIBTree() : head(tree_mib.set_head(CTrieNode("mib", 1)))
{
}