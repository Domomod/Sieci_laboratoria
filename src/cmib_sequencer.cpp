#include "cmib_sequencer.hpp"
#include "cmib_parser.hpp"
#include "cmib_object.hpp"

const char split_declarations_regexp[] = R"(\s*\w(?:.*?(OBJECT-TYPE).*\n(?:.*\n)*?.*::=.*?\n)|(?:(.*)?:=(.*\n)+?\n))";

int CmibFileSequencer::parse_all(const std::string& str)
{
    static const std::regex regexp(split_declarations_regexp);
    std::for_each(std::sregex_iterator(str.begin(), str.end(), regexp),
                    std::sregex_iterator(),
                    [] (const auto& match) {
                        if("OBJECT-TYPE" == match[1])
                        {
                        std::string str = match.str();
                        CMIBobject x = CmibParser::parse(CmibParser::parse_object, str);
                        }
                        else
                        {
                        std::string str = match.str();
                        type_declaration x = CmibParser::parse(CmibParser::parse_type_job, str);
                        }
                    });

    return 0;
};