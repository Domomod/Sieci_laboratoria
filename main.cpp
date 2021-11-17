#include <iostream>
#include <fstream>
#include <string>
#include <regex>

std::string mib_obj = 
"atEntry OBJECT-TYPE\
SYNTAX  AtEntry\
ACCESS  not-accessible\
STATUS  deprecated\
DESCRIPTION\
        \"Each entry contains one NetworkAddress to\
        `physical' address equivalence.\"\
INDEX   { atIfIndex,\
        atNetAddress }\
::= { atTable 1 }";

std::string obj_regex =
R"((?<identfier>\w*)\s*OBJECT-TYPE\s*?)"
R"(SYNTAX(?s)(?<syntax>.*)?)"
R"(ACCESS(?s)(?<access>.*)?)"
R"(STATUS(?s)(?<status>.*?))"
R"(DESCRIPTION(?s)(?<description>.*?))"
R"(INDEX(?s)(?<index>.*?)::=\s*?{((?<OID>).*?)})";

std::string type_regex = 
R"((?<type_name>\w*)\s*::=\s*)" //Type name
R"((?:\[(?<scope>APPLICATION)\s*(?<type_id>\d*)\])?)\s*)" //Scope and Type id (Optional) 
R"((--.*\n)?\s*(?<tag>IMPLICIT|EXPLICIT)?\s*)" //IMPLICIT EXPLICIT (Optional)
R"((?<type>(?:[\w\s]*)(?:{(?s).*})?))" //Type declaration
R"(?:\((?<restriction>.*)\))?)"; //Restrictions

std::string comment_regex = 
"(--.*\n)?";

std::string consecutive_comments_and_blank_lines = R"(^(\s*(--.*)?$)+)";

std::string split_regex = 
"^(?:\\s*(?:--.*)?$)+\\n"               // Block of lines that are empty (^\s*?$) or contain only comments(^\s*--.*?$). Ended with \n to allow matching of next groups
"(^[^-\\n]*OBJECT-TYPE(?:\\s|.)*?:=(?:\\s|.)*?^$^$)"; // Object-type group, the ^[^-\\n]* prevents matching comments like "-- this is IpAddr OBJECT-TYPE"
//"|"                                     // OR
//"(\\s*(\\w*)\\s*::=(?s).*?^$)"                     // Type declaration groups (might containt some comments at the end)
//"|"                                     // OR
//"(^[^-\\n]*IMPORTS(?s).*?^$)";           // Import declaration groups
                                        // All declaration lazy match to the first blank line and they can have trailing lines containing comments

int main()
{
    std::ifstream t("data/RFC1213-MIB.mib");
    std::string str((std::istreambuf_iterator<char>(t)),
                     std::istreambuf_iterator<char>());
    std::regex split(R"(\s*\w(?:.*?OBJECT-TYPE.*\n(?:.*\n)*?.*::=.*?\n)|(?:.*?:=(.*\n)+?\n))");

    for(std::sregex_iterator i = std::sregex_iterator(str.begin(), str.end(), split);
                             i!= std::sregex_iterator(); 
                             ++i)                        
    {       
        std::cout << (*i).str() << "\n\n===========================================\n\n";

    };
}