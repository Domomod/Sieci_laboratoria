#pragma once
#include <iostream>
#include <memory>
#include <vector>

#include "cmib_enum.hpp"

class CMIBType;

class CMIBobject
{

private:
    std::string IDENTI;
    std::string DESCRI;
    syntax_t _syntax;
    access_t _access;
    status_t _status;
    std::shared_ptr<CMIBType> type;

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

class CMIBType
{
private:
    bool is_derrived;
    syntax_t base_type;
    std::string derrived_type;

    std::shared_ptr<CMIBType> derrived_from; //nullptr if is_derrived == false
    union
    {
        std::vector<std::shared_ptr<CMIBType>> sequence; // can be empty
        std::shared_ptr<CMIBType> sequence_of; // variable size sequence of one type
    };

public:
    CMIBType() = delete;
    explicit CMIBType(const syntax_t & base_type, const std::string & name)  : base_type(base_type), derrived_type(name), is_derrived(false) 
    {
    }

    explicit CMIBType(const std::string & name)   : base_type(_SYNTAX_e_MAX_ENUM), derrived_type(name),  is_derrived(true)
    {
    }

    explicit CMIBType(std::vector<std::shared_ptr<CMIBType>> sequence) : sequence(sequence), is_derrived(false) , base_type(SEQUENCE) 
    {

    }

    explicit CMIBType(std::shared_ptr<CMIBType> sequence_of) :     sequence_of(sequence_of), is_derrived(false) , base_type(SEQUENCE_OF)
    {

    }

    void print()
    {

        switch (base_type.get())
        {
        case SEQUENCE:
            std::cout << "    SEQUENCE     ->\n";
            for(auto type_ptr : sequence)
            {
                std::cout << "\t\t" << type_ptr->derrived_type << ",\n";
            }
            break;
        case SEQUENCE_OF:
            std::cout  << "   SEQUENCE OF  ->" << sequence_of->derrived_type << "\n";
            break;
        default:
            std::cout << "  REGULAR  TYPE  ->" <<  derrived_type << "\n";
            break;
        }
    }

    ~CMIBType()
    {
        switch (base_type.get())
        {
            case SEQUENCE:
                sequence.~vector();
                break;
            case SEQUENCE_OF:
                sequence_of.~shared_ptr();
                break;
        }
    }
};