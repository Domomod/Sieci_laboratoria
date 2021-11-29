#include "../include/tree.hh"
#include <iostream>
#include <vector>
#include <map>


enum struct SYNTAX { INTEGER,
                     OCTET_STRING,
                     OBJECT_IDENTIFIER,
                     NULL_T,
                     IMPORT_S
}; // default type is int

enum struct ACCESS
{
    read_only,
    read_write,
    not_accessible
}; // default type is int
enum struct STATUS
{
    mandatory,
    deprecated
}; // default type is int

class CMIBobject
{ // Cmibobject
public:
    std::string IDENTI; //string

    SYNTAX syntax_scoped; // struct

    ACCESS access_scoped;
    STATUS status_scoped;

    std::string DESCRI;

    std::string get_IDENTI()
    {
        return (IDENTI);
    }

    SYNTAX get_SYNTAX()
    {
        return (syntax_scoped);
    }
    ACCESS get_ACCESS()
    {
        return (access_scoped);
    }
    STATUS get_STATUS()
    {
        return (status_scoped);
    }
    std::string get_DESCRI()
    {
        return (DESCRI);
    }

    
    void set_IDENTI(std::string s)
    {
        IDENTI = s;
    }
    void set_SYNTAX(SYNTAX syn_s)
    {
        syntax_scoped = syn_s;
    }

    void set_ACCESS(ACCESS ac_s)
    {
        access_scoped = ac_s;
    }
    void set_STATUS(STATUS s_s)
    {
        status_scoped = s_s;
    }

    void set_DESCRI(std::string s)
    {
        DESCRI = s;
    }
};

class CTrieNode
{
public:
    std::string name;
    int oid;
    CMIBobject object_mib_ptr;// = new CMIBobject;
   CTrieNode () = default;     
   
    CTrieNode (const std::string &name, int oid) : name(name),oid(oid)
    {
        
    }
    std::string get_name()
    {
        return (name);
    }
    void init(int i, std::string s)
    {
        name = s;
        oid = i;
    }
    void set_name(std::string s)
    {
        name = s;
    }
    int get_oid()
    {
        return (oid);
    }
    void set_name(int i)
    {
        oid = i;
    }
};

/*
bool check_existence(std::string name)
{
    if()
    {

        return false;
    }
    else
    {

        return true;
    }

} 

void put_in_tree(int oid, std::string name)
{
    CTrieNode node_child;
    if(check_existence(name))
    {

        //add to existing child - main -node 
    }
    else
    {

        //create new main child/node 
    }
} */

class CMIBTree
{

private:
    tree<CTrieNode> tree_mib;
    const tree<CTrieNode>::iterator head;
    std::map<std::string, std::vector<int>> oid_map;

public:
    int insert_add(const std::vector<int> &oid, const CTrieNode &node)
    {
        auto node_it = head;
        int depth = 0;

        std::cout<< node_it->get_name() << "\n";
        for(auto i : oid)
        {
            node_it++;
            while(i > 1)
            {
                node_it = node_it.next_skip_children();
                i--;
            }
            
            std::cout<< node_it->get_name() << "\n";
        }

        tree_mib.append_child(node_it, node);
        std::cout << "---------------------\n";

        return 0;
    }

    CMIBTree () : head(tree_mib.set_head(CTrieNode ("mib",1)))
    {

    }
};

int main(int, char **)
{
    CMIBTree cmibTree;
    cmibTree.insert_add({}, CTrieNode("system", 1));
    cmibTree.insert_add({}, CTrieNode("interfaces", 2));
    cmibTree.insert_add({1}, CTrieNode("dupa", 2));
    cmibTree.insert_add({1,1}, CTrieNode("DUUPA", 2));
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