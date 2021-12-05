#include "cmib_parser.hpp"
#include "cmib_regex.hpp"

namespace CmibParser{


CMIBobject parse_obj(const std::string& str)
{
    static const std::regex regexp(object_type_regexp_str);
    std::smatch match;
    std::regex_search(str, match, regexp);

    CMIBobject o;

    //const std::string & syntax_bloated = match[2].str(); 
    //std::cout << "SYNTAX:\t " << match[2] <<"\n";
    //syntax_t syntax = parse_syntax(syntax_bloated);

    // o.syntax(syntax);
    // o.access((access_t)match[3].str());
    // o.status((status_t)match[4].str());

    // std::cout << "IDENTI:\t" << match[1] << "\n";
    // std::cout << "ACCESS:\t" << match[3] << "\n";
    // std::cout << "STATUS:\t" << match[4] << "\n";
    // std::cout << "DESCRI:\t" << match[5] << "\n";
    // std::cout << "INDEX :\t" << match[6] << "\n";
    // std::cout << "OID   :\t" << match[7] << "\n";
    // std::cout << "==============================================\n\n\n";

    return o;
}

type_declaration parse_type(const std::string& str)
{
    static const std::regex regexp(type_declaration_regexp_str);
    std::smatch match;
    std::regex_search(str, match, regexp);

    // std::cout << str << "\n\n";

    // std::cout << "LABEL      :\t" << match[1] << "\n";
    // std::cout << "APPLICATION:\t" << match[2] << "\n";
    // std::cout << "ACCESS     :\t" << match[3] << "\n";
    std::cout << "TYPE       :\t" << match[4] << "\n";

    auto type = parse_syntax(match[4]);
    std::cout << "================[Parsed as]=====================\n\n\n";
    type->print();
    std::cout << "==============================================\n\n\n";



    return type_declaration{0};
}



std::shared_ptr<CMIBType> parse_syntax(const std::string& str)
{
    static const std::regex sequence_regexp(sequence_regexp_str);
    static const std::regex sequence_of_regexp(sequence_of_regexp_str);
    static const std::regex syntax_type(syntax_type_regexp_str);
    std::smatch match;

    std::shared_ptr<CMIBType> cmibType;
    if(std::regex_search(str, match, sequence_of_regexp))
    {
        std::string type = match[1];

        std::shared_ptr<CMIBType> seqOf;
        syntax_t syntax = (syntax_t) type;

        if (syntax.get() != _SYNTAX_e_MAX_ENUM)
            seqOf = std::make_shared<CMIBType>(syntax, type);
        else
            seqOf = std::make_shared<CMIBType>(type);

        cmibType = std::make_shared<CMIBType>(seqOf);
    }
    else if(std::regex_search(str, match, sequence_regexp))
    {
        std::vector<std::shared_ptr<CMIBType>> sequence;
        static const std::regex sequence_entry(sequence_entry_regexp_str);
        std::for_each(std::sregex_iterator(str.begin(), str.end(), sequence_entry),
                        std::sregex_iterator(),
                        [&] (const auto& match) {
                            std::string identifier = match[1];
                            std::string type = match[2];
                            if(!(identifier.empty() or type.empty()))
                            {
                                std::shared_ptr<CMIBType> seqEntry;
                                syntax_t syntax = (syntax_t) type;
                                if (syntax.get() != _SYNTAX_e_MAX_ENUM)
                                    seqEntry = std::make_shared<CMIBType>(syntax, type);
                                else
                                    seqEntry = std::make_shared<CMIBType>(type);

                                sequence.push_back(seqEntry);
                            }
                        });

        cmibType = std::make_shared<CMIBType>(sequence);
    }
    else if(std::regex_search(str, match, syntax_type))
    {
        std::string type = match[1];

        syntax_t syntax = (syntax_t) type;
        if (syntax.get() != _SYNTAX_e_MAX_ENUM)
            cmibType = std::make_shared<CMIBType>(syntax, type);
        else
            cmibType = std::make_shared<CMIBType>(type);
    }

    return cmibType;
}

};