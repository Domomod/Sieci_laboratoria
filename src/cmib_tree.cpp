#include "cmib_tree.hpp"





int CMIBTree ::insert_add(CTrieNode node)
{

   // if(find_name(node.get_name())
    //tree_mib.insert(top,node);
    std::cout << node.get_name();
    std::cout << "START insert_add";
    auto node_it = tree_mib.begin();
    int depth = 0;
    //get_name()
    for (auto i : oid_map[node.get_name()])
    {
        node_it++;
        while (i > 1)
        {
            node_it = node_it.next_skip_children();
            i--;
        }

        std::cout << node_it->get_name() << "\n";
        std::cout << node_it->get_oid() << "\n";
    }

    tree_mib.append_child(node_it,node);
    //oid_map.
    std::cout << "---------------------\n";

    return 0;
}
tree<CTrieNode>::iterator CMIBTree ::find_name(std::string name)
{
    std::cout << "--start looking for name--" << name  <<"----\n";
    auto node_it_out = tree_mib.begin();
   // auto node_it = tree_mib.begin();
  //  std::cout << node_it -> get_name();
    for (auto node_it = tree_mib.begin(); node_it != tree_mib.end(); ++node_it)
    {

       // std::cout << node_it->get_name() << "\n";
      //  std::cout << node_it->get_oid() << "\n";
      if(node_it-> get_name() == name)
      {
          std::cout << node_it->get_oid() << "\n";
          node_it_out = node_it;
          break;
      }

    }

    //std::cout << "searching start" << find_iter->get_name();
    return node_it_out;
}
tree<CTrieNode>::iterator CMIBTree ::find_oid(int oid)
{
    std::cout << "--start looking for oid--" << oid  <<"----\n";
    auto node_it_out = tree_mib.begin();
    // auto node_it = tree_mib.begin();
    //  std::cout << node_it -> get_name();
    for (auto node_it = tree_mib.begin(); node_it != tree_mib.end(); ++node_it)
    {

        // std::cout << node_it->get_name() << "\n";
        //  std::cout << node_it->get_oid() << "\n";
        if(node_it-> get_oid() == oid)
        {
            std::cout << node_it->get_name() << "\n";
            node_it_out = node_it;
            break;
        }

    }
    //std::cout << "searching start" << find_iter->get_name();
    return node_it_out;
}


tree<CTrieNode>::iterator CMIBTree ::find_oid2(const std::vector<int> &oid)
{
    auto node_it = head;
    int depth = 0;

    //
    int j = 6;
    for (auto i : oid)
    {
        if(j-- > 0 )
        {       continue;
        }

        node_it++;

        while (i > 1)
        {
            node_it = node_it.next_skip_children();
            i--;

        }



    }
    std::cout << node_it->get_name() << "\n";
    return node_it;
}

int CMIBTree ::insert_by_name(const std::string &name, const CTrieNode &node)
{
    auto strsd = node.get_name();
    auto node_it = find_name(name);
    tree_mib.append_child(node_it, node);
    std::cout << "----insert-by-name-----\n";
    std::cout << strsd << std::endl;
    return 0;
}

int CMIBTree ::insert_by_oid(const std::vector<int> &oid, const CTrieNode &node)
{
    std::cout << "insert by OID "  << std::endl;
    auto node_it = find_oid2(oid);
    std::cout << node_it -> get_name()  << std::endl;
    tree_mib.append_child(node_it, node);
    std::cout << "---------------------\n";

    return 0;
}

CMIBTree ::CMIBTree() : head(tree_mib.set_head(CTrieNode("mib", 0,"ISO")))
{
}