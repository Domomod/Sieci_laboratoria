#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <algorithm>

#include "cmib_sequencer.hpp"

int main()
{
    std::ifstream t("data/RFC1213-MIB.mib");
    std::string str((std::istreambuf_iterator<char>(t)),
                     std::istreambuf_iterator<char>());

    CmibFileSequencer::parse_all(str);
}