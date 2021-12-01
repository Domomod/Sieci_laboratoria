#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <algorithm>
#include <types.hpp>
#include <cmib_object.hpp>
#include <cmib_regex.hpp>

#pragma once

namespace CmibParser
{
    //╔══════════════════╗
    //║ Parser functions ║
    //╚══════════════════╝
    type_declaration parse_type(const std::smatch& match);
    CMIBobject parse_obj(const std::smatch& match);
    syntax_t parse_syntax(const std::smatch& match);

    //╔════════════════════════════════════════╗
    //║ Type safe function parameter structure ║
    //╚════════════════════════════════════════╝
    enum class regexp_type : uint_fast8_t
    { mib_file, object_decl, type_decl, syntax_decl };

    template<regexp_type x, class T> 
    struct regex_job 
    {
        const char* str; 
        T (*const foo) (const std::smatch& match); 
    };

    const regex_job<regexp_type::object_decl, CMIBobject> 
        parse_object {object_type_regexp_str, parse_obj};
    const regex_job<regexp_type::type_decl, type_declaration> 
        parse_type_job {type_declaration_regexp_str, parse_type};
    const regex_job<regexp_type::syntax_decl, syntax_t> 
        parse_syntax_job {syntax_type_regexp_str, parse_syntax};

    //╔═══════════════════════════╗
    //║ Stateless parser function ║
    //╚═══════════════════════════╝
    template<class regex_job>
    decltype(regex_job::foo(std::smatch())) parse(regex_job job , const std::string& str)
    {
        static const std::regex regexp(job.str);
        std::smatch match;
        std::regex_search(str, match, regexp);

        return job.foo(match);
    }
}