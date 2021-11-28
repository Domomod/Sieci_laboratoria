#include "../include/tree.hh"
#include <iostream>

/*
struct INTEGER{
    int value;
    int size;
};
struct OCTET_STRING{
    int 
};
struct OBJECT_IDENTIFIER{

};
struct NULL_T{

}; */

class CDataType {
public:
std::string IDENTI;
std::string SYNTAX;
std::string ACCESS;
std::string STATUS;
std::string DESCRI;

std::string get_IDENTI(){
return (IDENTI);
}
std::string get_SYNTAX(){
return (SYNTAX);
}
std::string get_ACCESS(){
return (ACCESS);
}
std::string get_STATUS(){
return (STATUS);
}
std::string get_DESCRI(){
return (DESCRI);
}

void set_IDENTI(std::string s){
IDENTI = s;
}
void set_SYNTAX(std::string s){
SYNTAX = s;
}
void set_ACCESS(std::string s){
ACCESS = s;
}
void set_STATUS(std::string s){
STATUS = s;
}
void set_DESCRI(std::string s){
DESCRI = s;
}


};

class CTrieNode : public CDataType {
public:

std::string name;
int oid;
std::string get_name(){
return (name);
}

void set_name(std::string s){
name = s;
}
int get_oid()
{
    return (oid);
}
void set_name(int i){
oid = i;
}

};


int main(int, char **)
   {
       tree<CTrieNode> tree_root_it;
       tree<CTrieNode>::iterator node_root,node_child;
       node_root=tree_root_it.begin();
       CTrieNode node_child_TEST;
       node_child_TEST.ACCESS = "string_test";
       node_child=tree_root_it.insert(node_root,node_child_TEST);
       tree<CTrieNode>::iterator its = tree_root_it.begin();
       CTrieNode test = *its;
       std::cout << test.get_ACCESS();
       //node.ACCESS = "ll";
   }