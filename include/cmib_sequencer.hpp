#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <algorithm>
#include "types.hpp"

#pragma once

namespace CmibFileSequencer
{
    template<class regex_job>
    decltype(regex_job::foo(std::smatch())) parse(regex_job job , const std::string& str)
    {
        static const std::regex regexp(job.str);
        std::smatch match;
        std::regex_search(str, match, regexp);

        //std::cout << "==============================================\n";
        //std::cout << match.str() << "\n";
        //std::cout << "==============================================\n";

        return job.foo(match);
    }

    int parse_all(const std::string& str);
}