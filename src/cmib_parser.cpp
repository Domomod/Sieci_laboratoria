#include "cmib_parser.hpp"
#include "cmib_regex.hpp"
#include "tuple"
#include <regex>

namespace CmibParser{
using namespace CmibRegex;

std::tuple<std::shared_ptr<CMIBobject>,std::string,int> parse_obj(
        const std::string& str
    )
{    
    std::smatch match;
    static const std::regex type_definition_regexp(object_type_regexp_str);
    std::regex_search(str, match, type_definition_regexp);



    std::cout << str << "\n";
    std::cout << "IDENTI:\t" << match[1] << "\n";
    std::cout << "SYNTAX:\t" << match[2] << "\n";
    std::cout << "ACCESS:\t" << match[3] << "\n";
    std::cout << "STATUS:\t" << match[4] << "\n";
    std::cout << "DESCRI:\t" << match[5] << "\n";
    std::cout << "INDEX :\t" << match[6] << "\n";
    std::cout << "OID   :\t" << match[7] << "\n";
    std::regex rgx("\\s+");
    std::string OIDNAME_TO_SPLIT = match[7].str();
    std::sregex_token_iterator iter(OIDNAME_TO_SPLIT.begin(),OIDNAME_TO_SPLIT.end(),rgx,-1);
    std::sregex_token_iterator end;
    ++iter;
    std::string name_to_return = *iter;
    ++iter;
    std::string oid_to_return = *iter;
    //for ( ; iter != end; ++iter)
     //   std::cout << *iter << '\n';
    std::cout <<name_to_return << "\n";
    std::cout << oid_to_return<< "\n";
    std::cout << "==============================================\n\n\n";
    int oid_to_return_int = std::stoi(oid_to_return);
    std::string syntax_bloated = match[2].str();

    std::smatch type_match;
    static const std::regex simple_syntax_regexp(object_simple_syntax_regexp_str);
    std::regex_search(syntax_bloated, type_match, simple_syntax_regexp);
    if(type_match[0].matched and type_match[0].str().find("SEQUENCE") == std::string::npos)
    {
        return  {std::make_shared<CMIBobject>(
            match[1],
            match[5],
            (access_t) match[3].str(),
            (status_t) match[4].str(),
            type_match[1]
        ),name_to_return,oid_to_return_int};
    }
    else
    {
        std::shared_ptr<CMIBType> type = parse_syntax(syntax_bloated);

        return {std::make_shared<CMIBobject>(
            match[1],
            match[5],
            (access_t) match[3].str(),
            (status_t) match[4].str(),
            type
        ),name_to_return,oid_to_return_int};
    }
}

std::tuple<std::string, std::shared_ptr<CMIBType>> parse_type(
        const std::string& str
    )
{
    static const std::regex regexp(type_declaration_regexp_str);
    std::smatch match;
    std::regex_search(str, match, regexp);

    // std::cout << str << "\n\n";

    std::cout <<  "================[parsing  ]=====================\n";
    std::cout << str << "\n";
    std::cout << "LABEL      : |" << match[1] << "|\n";
    std::cout << "APPLICATION: |" << match[2] << "|\n";
    std::cout << "ACCESS     : |" << match[3] << "|\n";
    std::cout << "TYPE       : |" << match[4] << "|\n";

    auto type = parse_syntax(match[4]);
    type->type_name = match[1];
    type->application = match[2];
    type->implicitness = match[3];

    std::cout << "================[Parsed as]=====================\n";
    type->print();
    std::cout << "==============================================\n\n\n";
    

    return {match[1], type};
}

std::shared_ptr<CMIBType> make_CmibType(
    const std::string& derrived_name, 
    const std::string& restriction, 
    _SYNTAX_e e
    )
{
    std::shared_ptr<CMIBType> cmibType;
    cmibType = std::make_shared<CMIBType>(std::shared_ptr<CMIBType>(nullptr), e);
    cmibType->derrived_name = derrived_name;
    cmibType->restrictions = restriction;
    
    return cmibType;
}

std::shared_ptr<CMIBType> parse_syntax(
        const std::string& str
    )
{
    static const std::regex sequence_regexp(sequence_regexp_str);
    static const std::regex sequence_of_regexp(sequence_of_regexp_str);
    static const std::regex syntax_type(syntax_type_regexp_str);
    std::smatch match;

    std::shared_ptr<CMIBType> cmibType;
    if(std::regex_search(str, match, sequence_of_regexp))
    {
        std::string derrived_name = match[1];
        std::string restrictions = match[2];
        cmibType = make_CmibType( derrived_name, restrictions, SEQUENCE_OF);
    }
    else if(std::regex_search(str, match, sequence_regexp))
    {
        std::vector<std::shared_ptr<CMIBType>> sequence;
        static const std::regex sequence_entry(sequence_entry_regexp_str);
        std::for_each(std::sregex_iterator(str.begin(), str.end(), sequence_entry),
                        std::sregex_iterator(),
                        [&] (const auto& match) {
                            std::string identifier = match[1];
                            std::string derrived_name = match[2];
                            std::string restrictions = match[3];

                            if(!(identifier.empty() or derrived_name.empty()))
                            {
                                std::cout << "Sequence member " << identifier << " is derrived from " << derrived_name << " and has restrictions (" << restrictions << ")\n";
                                auto sequence_type = make_CmibType(derrived_name, restrictions, DERRIVED_TYPE);
                                sequence_type->type_name = identifier;
                                sequence.push_back(
                                    sequence_type
                                );
                            }
                        });

        cmibType = std::make_shared<CMIBType>(sequence);
    }
    else if(std::regex_search(str, match, syntax_type))
    {
        std::string derrived_name = match[1];
        std::string restrictions = match[2];
        std::cout << "DERRIVED  REG|" << derrived_name << "|\n";
        cmibType = make_CmibType( derrived_name, restrictions, DERRIVED_TYPE);
    }

    return cmibType;
}

};