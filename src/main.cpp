#include "../include/tree.hh"
#include <iostream>

enum struct SYNTAX {INTEGER, OCTET_STRING,OBJECT_IDENTIFIER,NULL_T,IMPORT_S}; // default type is int

enum struct ACCESS {read_only, read_write, not_accessible }; // default type is int
enum struct STATUS {mandatory, deprecated }; // default type is int

class CDataType {
public:
std::string IDENTI; //string

SYNTAX syntax_scoped; // struct 

ACCESS access_scoped;
STATUS status_scoped;

std::string DESCRI;

std::string get_IDENTI(){
return (IDENTI);
}

SYNTAX get_SYNTAX(){
return (syntax_scoped);
}
ACCESS get_ACCESS(){
return (access_scoped);
}
STATUS get_STATUS(){
return (status_scoped);
}
std::string get_DESCRI(){
return (DESCRI);
}

void set_IDENTI(std::string s){
IDENTI = s;
}
void set_SYNTAX(SYNTAX syn_s){
syntax_scoped = syn_s;
}

void set_ACCESS(ACCESS ac_s){
access_scoped = ac_s;
}
void set_STATUS(STATUS s_s){
status_scoped = s_s;
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
       //node_child_TEST.ACCESS = "string_test";
       node_child=tree_root_it.insert(node_root,node_child_TEST);
       tree<CTrieNode>::iterator its = tree_root_it.begin();
       CTrieNode test = *its;
       //std::cout << test.get_ACCESS();
       //node.ACCESS = "ll";
   }