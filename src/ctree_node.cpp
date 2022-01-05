#include "ctree_node.hpp"

CTrieNode::CTrieNode() = default;

CTrieNode::CTrieNode(const std::string &name, int oid,const std::string &parent_name) : name(name), oid(oid)
{
}
std::string CTrieNode::get_name() const {
    return (name);
}
void CTrieNode::init(int i, std::string s)
{
    name = s;
    oid = i;
}
void CTrieNode::set_name(std::string s)
{
    name = s;
}
int CTrieNode::get_oid()
{
    return (oid);
}
void CTrieNode::set_oid(int i)
{
    oid = i;
}

std::string CTrieNode::get_parent_name() const {
    return (parent_name);
}