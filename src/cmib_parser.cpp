#include "cmib_parser.hpp"


namespace CmibParser{


CMIBobject parse_obj(const std::smatch& match)
{
    CMIBobject o;
    
    const std::string & syntax_bloated = match[2].str(); 
    syntax_t syntax = parse(parse_syntax_job, syntax_bloated);

    o.syntax(syntax);
    o.access((access_t)match[3].str());
    o.status((status_t)match[4].str());

    
    // std::cout << "IDENTI:\t" << match[1] << "\n";
    std::cout << "SYNTAX:\t" << syntax << " evaluated from " << match[2] <<"\n";
    //std::cout << "ACCESS:\t" << o.access() << "\t||\t|" << match[3] <<"|\n";
    //std::cout << "STATUS:\t" << o.status() << "\t||\t|" << match[4] <<"|\n";
    // std::cout << "DESCRI:\t" << match[5] << "\n";
    // std::cout << "INDEX :\t" << match[6] << "\n";
    // std::cout << "OID   :\t" << match[7] << "\n";
    // std::cout << "==============================================\n\n\n";

    return o;
};

type_declaration parse_type(const std::smatch& match)
{
    // std::cout << "LABEL      :\t" << match[1] << "\n";
    // std::cout << "APPLICATION:\t" << match[2] << "\n";
    // std::cout << "ACCESS     :\t" << match[3] << "\n";
    // std::cout << "TYPE       :\t" << match[4] << "\n";
    // std::cout << "RESTRICTION:\t" << match[5] << "\n";
    // std::cout << "==============================================\n\n\n";


    return type_declaration{0};
};

syntax_t parse_syntax(const std::smatch& match)
{

    std::string type_name = match[1].str();
    std::cout << "SYNTAX:\t|" << match.str() <<"|\n";
    std::cout << "SYNTAX:\t|" << type_name <<"|\n";

    return (syntax_t) type_name;
};

}