#include "cmib_sequencer.hpp"
#include "cmib_parser.hpp"
#include "cmib_object.hpp"
#include "cmib_regex.hpp"

using namespace CmibRegex;

int CmibFileSequencer::initialize(const std::string& path)
{

    types_map.emplace("NULL"              , std::make_shared<CMIBType>(NULL_T));
    types_map.emplace("INTEGER"           , std::make_shared<CMIBType>(INTEGER));
    types_map.emplace("OCTET STRING"      , std::make_shared<CMIBType>(OCTET_STRING));
    types_map.emplace("OBJECT IDENTIFIER" , std::make_shared<CMIBType>(OBJECT_IDENTIFIER));

    parse_file(path);

    std::cout << "Known types are:\n";
    for(const auto& elem : types_map)
    {
        std::cout << "\t" <<elem.first << ",\n";
    }

    std::cout << "Known objects are:\n";
    for(const auto& elem : parsed_objects)
    {
        std::cout << "\t" <<elem->name() << ",\n";
    }


    fill_derrived_types();

    return 0;
}

int CmibFileSequencer::parse_file(const std::string& path)
{
    if(already_parsed_guard.count(path))
    {
        std::cout << "[LOG-INFO] Ommiting already parsed file - " << path << "\n";
        return 0;
    }
    already_parsed_guard.emplace(path);

    std::cout << "[LOG-INFO] Parsing file - " << path << "\n";
    std::ifstream t(path);
    if (!t)
    {
        throw std::runtime_error("Failed to open mib file.");
    }
    std::string file_body((std::istreambuf_iterator<char>(t)),
                           std::istreambuf_iterator<char>());

    std::size_t pos = file_body.find(definitions_begin_substr);
    pos += sizeof(definitions_begin_substr);
    std::string definitions = file_body.substr(pos);
    // std::cout << "FILE\n" << definitions;
    parse_dependencies(definitions);
    return 0;
}

int CmibFileSequencer::process_imports(const std::string& imports_definiton)
{
    static const std::regex regexp(imports_entry_regexp);
        std::for_each(std::sregex_iterator(imports_definiton.begin(), imports_definiton.end(), regexp),
                    std::sregex_iterator(),
                    [&] (const auto& match) {
                        std::string import_name = match[1];
                        std::string import_path = "data/" + import_name + ".mib";
                        parse_file(import_path);
                    });
    return 0;
}

int CmibFileSequencer::fill_derrived_types()
{
    for(auto & [name, type] : types_map)
    {
        std::cout << "\n---------------------------------------------------------------------\n";
        std::cout << "Deterimining type dependencies of " << name << " type\n";
        type->set_derrived_type(types_map);
    }

        for(auto & object_ptr: parsed_objects)
    {
        std::cout << "\n---------------------------------------------------------------------\n";
        std::cout << "Deterimining type dependencies of " << object_ptr->name() << " object\n";
        object_ptr->set_derrived_type(types_map);
    }

    return 0;
}

int CmibFileSequencer::parse_dependencies(const std::string& str)
{
    static const std::regex regexp(split_declarations_regexp);
    std::for_each(std::sregex_iterator(str.begin(), str.end(), regexp),
                    std::sregex_iterator(),
                    [&] (const auto& match) {
                        // std::cout << "===============\n" << match[0] << "\n";
                        // std::cout << "TOKEN-1 :: |" << match[1] << "|\n";
                        // std::cout << "TOKEN-2 :: |" << match[2] << "|\n";
                        // std::cout << "TOKEN-3 :: |" << match[3] << "|\n";
                        
                        if ("IMPORTS" == match[1])
                        {
                            std::cout << match.str() << "\n";
                            process_imports(match.str());
                        }
                        else if ("EXPORTS" == match[1])
                        {
                            //std::cout << match.str() << "\n";
                        }
                        else if ("MACRO" == match[2])
                        {
                            //std::cout << match.str() << "\n";
                        }
                        else if ("OBJECT-IDENTITY" == match[3])
                        {
                            //std::cout << match.str() << "\n";
                        }
                        else if ("OBJECT IDENTIFIER" == match[3])
                        {
                            //std::cout << match.str() << "\n";
                        }
                        else if("OBJECT-TYPE" == match[3])
                        {
                            std::cout << "===============\n" << match[0] << "\n";
                            std::cout << "Parsing object\n";

                            std::string str = match.str();
                            std::shared_ptr<CMIBobject> x = CmibParser::parse_obj(str);
                            parsed_objects.push_back(x);
                        }
                        else
                        {
                            if(str.find("::= TEXTUAL-CONVENTION") != std::string::npos)
                            {
                                // Ignore Textual Conventions
                            }   
                            else
                            {
                                std::cout << "===============\n" << match[0] << "\n";

                                std::string str = match.str();
                                auto [name, type] = CmibParser::parse_type(str);
                                types_map.emplace(name, type);
                            }
                        }
                    });

    return 0;
};