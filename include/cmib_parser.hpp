#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <algorithm>
#include <types.hpp>
#include <cmib_object.hpp>

#pragma once

namespace CmibParser
{
    //╔═══════════════════════════╗
    //║ Stateless parser function ║
    //╚═══════════════════════════╝

    CMIBobject parse_obj(const std::string& str);

    type_declaration parse_type(const std::string& str);

    std::shared_ptr<CMIBType> parse_syntax(const std::string& str);
}