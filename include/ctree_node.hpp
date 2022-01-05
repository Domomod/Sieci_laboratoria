#pragma once
#include "cmib_object.hpp"

class CTrieNode
{
private:
    std::string name;
    std::string parent_name;
    int oid;
    std::shared_ptr<CMIBobject> object_mib_ptr;

public:
    CTrieNode();
    CTrieNode(const std::string &name, int oid,const std::string &parent_name);

    std::string get_name() const;

    void init(int i, std::string s);

    void set_name(std::string s);

    int get_oid();
    std::string get_parent_name() const;
    void set_oid(int i);
};
