#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <algorithm>
#include <types.hpp>
#include <cmib_regex.hpp>

#pragma once

namespace CmibParser
{
    enum class regexp_type : uint_fast8_t
    {
        mib_file, object_decl, type_decl
    };

    template<regexp_type x, class T> 
    struct regex_job 
    {
        const char* str; 
        T (*const foo) (const std::smatch& match); 
    };

    template<class regex_job>
    decltype(regex_job::foo(std::smatch())) parse(regex_job job , const std::string& str)
    {
        static const std::regex regexp(job.str);
        std::smatch match;
        std::regex_search(str, match, regexp);

        return job.foo(match);
    }

    type_declaration parse_type(const std::smatch& match);
    object_type parse_obj(const std::smatch& match);


    const regex_job<regexp_type::object_decl, object_type> parse_object {object_type_regexp_str, parse_obj};
    const regex_job<regexp_type::type_decl, type_declaration> parse_type_job {type_declaration_regexp_str, parse_type};

}