#pragma once
#include "CMIBenum.hpp"
#include "string.h"
#include <iostream>

class CMIBobject
{

private:
    std::string IDENTI;
    SYNTAX syntax_scoped;
    ACCESS access_scoped;
    STATUS status_scoped;
    std::string DESCRI;

public:
    std::string get_IDENTI();

    SYNTAX get_SYNTAX();

    ACCESS get_ACCESS();

    STATUS get_STATUS();

    std::string get_DESCRI();

    void set_IDENTI(std::string s);

    void set_SYNTAX(SYNTAX syn_s);

    void set_ACCESS(ACCESS ac_s);

    void set_STATUS(STATUS s_s);

    void set_DESCRI(std::string s);
};