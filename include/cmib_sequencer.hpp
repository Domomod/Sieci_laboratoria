#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <algorithm>
#include <set>
#include "cmib_object.hpp"

#pragma once

class CmibFileSequencer
{
    private:
        std::set<std::string> already_parsed_guard;
        std::map<std::string, std::shared_ptr<CMIBType>> types_map;
        std::vector<std::shared_ptr<CMIBobject>> parsed_objects;
    public:
        int initialize(const std::string& path);
        int parse_file(const std::string& path);
        int fill_derrived_types();
        int process_imports(const std::string& imports_definiton);
        int parse_dependencies(const std::string& str);
};