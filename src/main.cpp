#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <algorithm>

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

namespace parser
{
    namespace
    {
        enum class regexp_type : uint_fast8_t
        {
            mib_file, object_decl, type_decl
        };
    
    
        typedef std::tuple<const regexp_type, const char*> parse_string;

        
    }

    extern const char split_declarations_regexp[] = R"(\s*\w(?:.*?(OBJECT-TYPE).*\n(?:.*\n)*?.*::=.*?\n)|(?:(.*)?:=(.*\n)+?\n))";

    const auto parse_file = std::make_tuple(regexp_type::mib_file, split_declarations_regexp);
    const auto parse_object = std::make_tuple(regexp_type::mib_file, split_declarations_regexp);

    struct object_type { int x; };
    struct declaration_type { int y; };

    template<const char* regext_str, class Type>
    Type parse(const std::string& str)
    {
        static const std::regex regexp(regext_str);
        std::smatch match;
        std::regex_search(str, match, regexp);
        
        return Type{0};
    }

    int parse_all(const std::string& str)
    {
        static const std::regex regexp(split_declarations_regexp);
        std::for_each(std::sregex_iterator(str.begin(), str.end(), regexp),
                      std::sregex_iterator(),
                      [] (const auto& match) {
                          if("OBJECT-TYPE" == match[1])
                          {
                            std::string str = match.str();
                            object_type x = parse<split_declarations_regexp, object_type>(str);
                          }
                      });

        return 0;
    };

}

int main()
{
    std::ifstream t("data/RFC1213-MIB.mib");
    std::string str((std::istreambuf_iterator<char>(t)),
                     std::istreambuf_iterator<char>());

    parser::parse_all(str);

}