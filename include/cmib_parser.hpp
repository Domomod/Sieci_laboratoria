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

    std::tuple<std::shared_ptr<CMIBobject>,std::string,int> parse_obj(
        const std::string& str
    );

    std::tuple<std::string, std::shared_ptr<CMIBType>> parse_type(
        const std::string& str
    );

    std::shared_ptr<CMIBType> parse_syntax(
        const std::string& str
    );
}