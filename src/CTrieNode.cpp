#include "../include/CTrieNode.hpp"

CTrieNode::CTrieNode() = default;

CTrieNode::CTrieNode(const std::string &name, int oid) : name(name), oid(oid)
{
}
std::string CTrieNode::get_name()
{
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
void CTrieNode::set_name(int i)
{
    oid = i;
}
