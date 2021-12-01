#pragma once
#include <iostream>

#include "cmib_enum.hpp"

class CMIBobject
{

private:
    std::string IDENTI;
    std::string DESCRI;
    syntax_t _syntax;
    access_t _access;
    status_t _status;

public:

    syntax_t syntax() { return _syntax; };
    access_t access() { return _access; };
    status_t status() { return _status; };

    std::string get_IDENTI();
    std::string get_DESCRI();

    void set_IDENTI(std::string s);
    void set_DESCRI(std::string s);

    void syntax(const syntax_t& val) {_syntax = val; };
    void access(const access_t& val) {_access = val; };
    void status(const status_t& val) {_status = val; };

};