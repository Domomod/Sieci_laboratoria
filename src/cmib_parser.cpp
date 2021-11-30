#include "cmib_parser.hpp"

namespace CmibParser{


object_type parse_obj(const std::smatch& match)
{
    std::cout << "IDENTI:\t" << match[1] << "\n";
    std::cout << "SYNTAX:\t" << match[2] << "\n";
    std::cout << "ACCESS:\t" << match[3] << "\n";
    std::cout << "STATUS:\t" << match[4] << "\n";
    std::cout << "DESCRI:\t" << match[5] << "\n";
    std::cout << "INDEX :\t" << match[6] << "\n";
    std::cout << "OID   :\t" << match[7] << "\n";
    std::cout << "==============================================\n\n\n";

    return object_type{0};
};

type_declaration parse_type(const std::smatch& match)
{
    std::cout << "LABEL      :\t" << match[1] << "\n";
    std::cout << "APPLICATION:\t" << match[2] << "\n";
    std::cout << "ACCESS     :\t" << match[3] << "\n";
    std::cout << "TYPE       :\t" << match[4] << "\n";
    std::cout << "RESTRICTION:\t" << match[5] << "\n";
    std::cout << "==============================================\n\n\n";


    return type_declaration{0};
};

}