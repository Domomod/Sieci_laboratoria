#pragma once
#include "cmib_object.hpp"

class CTrieNode
{
private:
    std::string name;
    int oid;
    std::shared_ptr<CMIBobject> object_mib_ptr;

public:
    CTrieNode();
    CTrieNode(const std::string &name, int oid);

    std::string get_name();

    void init(int i, std::string s);

    void set_name(std::string s);

    int get_oid();

    void set_name(int i);
};
